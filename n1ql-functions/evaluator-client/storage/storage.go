package storage

import (
	"encoding/json"
	"log"

	"github.com/couchbase/cbauth/metakv"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
)

const (
	Namespace     = "/n1ql-functions/"
	FunctionsPath = Namespace + "functions/"
)

type Storage struct {
	addFunction  func(function *adapter.Function) error
	stopObserver chan struct{}
}

func New(addFunction func(function *adapter.Function) error) *Storage {
	s := &Storage{
		addFunction:  addFunction,
		stopObserver: make(chan struct{}),
	}
	s.observeFunctionsPath()
	return s
}

func (s *Storage) Stop() {
	s.stopObserver <- struct{}{}
}

func (s *Storage) AddFunction(function *adapter.Function) error {
	data, err := json.Marshal(function)
	if err != nil {
		return err
	}

	err = metakv.Set(FunctionsPath+function.Name, data, nil)
	if err != nil {
		return err
	}
	return nil
}

func (s *Storage) observeFunctionsPath() {
	go func() {
		for {
			err := metakv.RunObserveChildren(FunctionsPath,
				s.handleFunctionsPath, s.stopObserver)
			if err != nil {
				log.Printf("Error in metakv, err : %v", err)
			} else {
				return
			}
		}
	}()
}

func (s *Storage) handleFunctionsPath(path string, value []byte, rev interface{}) error {
	log.Printf("%s", path)
	if value == nil {
		// TODO : Handle Function delete
		return nil
	}

	function := &adapter.Function{}
	err := json.Unmarshal(value, function)
	if err != nil {
		return err
	}
	err = s.addFunction(function)
	if err != nil {
		return err
	}
	return nil
}
