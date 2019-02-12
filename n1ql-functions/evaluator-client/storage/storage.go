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
	addLibrary   func(function *adapter.Library) error
	stopObserver chan struct{}
}

func New(addLibrary func(library *adapter.Library) error) *Storage {
	s := &Storage{
		addLibrary:  addLibrary,
		stopObserver: make(chan struct{}),
	}
	s.observeFunctionsPath()
	return s
}

func (s *Storage) Stop() {
	s.stopObserver <- struct{}{}
}

func (s *Storage) AddLibrary(library *adapter.Library) error {
	data, err := json.Marshal(library)
	if err != nil {
		return err
	}

	err = metakv.Set(FunctionsPath+ library.Name, data, nil)
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

	library := &adapter.Library{}
	err := json.Unmarshal(value, library)
	if err != nil {
		return err
	}
	err = s.addLibrary(library)
	if err != nil {
		return err
	}
	return nil
}
