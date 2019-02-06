package client

import "github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"

type Resource struct {
	threadID          string
	evaluatorInstance *evaluator.Evaluator
}

type Scheduler struct {
	Resources    chan *Resource
	numResources uint32
}

func NewScheduler(numResources uint32) *Scheduler {
	return &Scheduler{
		Resources:    make(chan *Resource, numResources),
		numResources: numResources,
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
	for i := uint32(0); i < s.numResources; i++ {
		<-s.Resources
	}
	s.numResources = 0
}
