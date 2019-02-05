package client

import "github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"

type Scheduler struct {
	resources map[string]*evaluator.Evaluator
}

func NewScheduler() *Scheduler {
	return &Scheduler{
		resources: make(map[string]*evaluator.Evaluator),
	}
}

func (s *Scheduler) AddResources(threadIDs []string, evaluatorInstance *evaluator.Evaluator) {
	for i := 0; i < len(threadIDs); i++ {
		s.resources[threadIDs[i]] = evaluatorInstance
	}
}
