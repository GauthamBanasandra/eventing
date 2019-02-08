package client

import (
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"
)

type Resource struct {
	threadID          string
	evaluatorInstance *evaluator.Evaluator
}

type Scheduler struct {
	Resources chan *Resource
	config    *adapter.Configuration
}

func NewScheduler(config *adapter.Configuration) *Scheduler {
	return &Scheduler{
		Resources: make(chan *Resource, config.ThreadsPerWorker*config.WorkersPerNode),
		config:    config,
	}
}

func (s *Scheduler) AddResources(threadIDs []string, evaluatorInstance *evaluator.Evaluator) {
	for i := 0; i < len(threadIDs); i++ {
		s.Resources <- &Resource{
			threadID:          threadIDs[i],
			evaluatorInstance: evaluatorInstance,
		}
	}
}

func (s *Scheduler) FreeResources() {
	numResources := s.config.WorkersPerNode * s.config.ThreadsPerWorker
	for i := uint32(0); i < numResources; i++ {
		<-s.Resources
	}
}
