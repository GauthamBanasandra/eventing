package babysitter

import (
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/common"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/process"
	"github.com/couchbase/eventing/util"
)

const evaluatorPath = "/Users/gautham/projects/github/couchbase/mad-hatter/cmake-build-debug/goproj/src/github.com/couchbase/eventing/n1ql-functions/evaluator/evaluator"

type Babysitter struct {
	notificationPort port.Port
	evaluators       []*process.Process
}

func New(notificationPort port.Port) (*Babysitter, error) {
	return &Babysitter{
		notificationPort: notificationPort,
	}, nil
}

func (b *Babysitter) AddEvaluator() (common.EvaluatorID, error) {
	invalidId := common.EvaluatorID("")
	uuidGen, err := util.NewUUID()
	if err != nil {
		return invalidId, err
	}

	evaluatorId := common.EvaluatorID(uuidGen.Str())
	evaluator, err := process.NewProcess(evaluatorPath,
		[]string{
			b.notificationPort.ToString(),
			string(evaluatorId),
		})
	if err != nil {
		return invalidId, err
	}

	b.evaluators = append(b.evaluators, evaluator)
	return evaluatorId, nil
}
