package babysitter

import (
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/process"
	"github.com/couchbase/eventing/util"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/configuration"
	"strconv"
)

const evaluatorPath = "/Users/gautham/projects/github/couchbase/mad-hatter/cmake-build-debug/goproj/src/github.com/couchbase/eventing/n1ql-functions/evaluator/evaluator"

type Babysitter struct {
	config           *configuration.Configuration
	notificationPort port.Port
	evaluators       []*process.Process
}

func New(config *configuration.Configuration, notificationPort port.Port) (*Babysitter, error) {
	return &Babysitter{
		config: config,
		notificationPort: notificationPort,
	}, nil
}

func (b *Babysitter) AddEvaluator() (evaluator.ID, error) {
	invalidId := evaluator.ID("")
	uuidGen, err := util.NewUUID()
	if err != nil {
		return invalidId, err
	}

	evaluatorId := evaluator.ID(uuidGen.Str())
	evaluatorProcess, err := process.NewProcess(evaluatorPath,
		[]string{
			b.notificationPort.ToString(),
			string(evaluatorId),
			strconv.Itoa(int(b.config.ThreadsPerWorker)),
		})
	if err != nil {
		return invalidId, err
	}

	b.evaluators = append(b.evaluators, evaluatorProcess)
	return evaluatorId, nil
}
