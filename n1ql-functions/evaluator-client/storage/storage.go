package storage

import (
	"log"

	"github.com/couchbase/cbauth/metakv"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
)

const (
	Namespace     = "/n1ql-functions/"
	FunctionsPath = Namespace + "functions/"
)

type Storage struct {
	AddFunction  func(function *adapter.Function) error
	stopObserver chan struct{}
}

func New(addFunction func(function *adapter.Function) error) *Storage {
	s := &Storage{
		AddFunction:  addFunction,
		stopObserver: make(chan struct{}),
	}
	s.observeFunctionsPath()
	return s
}

func (s *Storage) Stop() {
	s.stopObserver <- struct{}{}
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

	return nil
}
