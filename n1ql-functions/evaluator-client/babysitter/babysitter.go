package babysitter

import (
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/process"
)

const evaluatorPath = "/Users/gautham/projects/github/couchbase/mad-hatter/cmake-build-debug/goproj/src/github.com/couchbase/eventing/n1ql-functions/evaluator/evaluator"

type Babysitter struct {
	notificationPort string
	evaluators       []*process.Process
}

func NewBabysitter(notificationPort string) (*Babysitter, error) {
	return &Babysitter{
		notificationPort: notificationPort,
	}, nil
}

func (b *Babysitter) AddEvaluator() error {
	evaluator, err := process.NewProcess(evaluatorPath, []string{b.notificationPort})
	if err != nil {
		return err
	}

	b.evaluators = append(b.evaluators, evaluator)
	return nil
}

func (b *Babysitter) AddEvaluators(num uint32) error {
	for i := uint32(0); i < num; i++ {
		err := b.AddEvaluator()
		if err != nil {
			return err
		}
	}
	return nil
}
