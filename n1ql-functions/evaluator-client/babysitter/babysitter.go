package babysitter

import (
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/process"
	"github.com/couchbase/eventing/util"
	"strconv"
)

const evaluatorPath = "/Users/gautham/projects/github/couchbase/mad-hatter/cmake-build-debug/goproj/src/github.com/couchbase/eventing/n1ql-functions/evaluator/evaluator"

type Babysitter struct {
	config           *adapter.Configuration
	notificationPort port.Port
	evaluators       []*process.Process
}

func New(config *adapter.Configuration, notificationPort port.Port) (*Babysitter, error) {
	return &Babysitter{
		config:           config,
		notificationPort: notificationPort,
	}, nil
}

func (b *Babysitter) AddEvaluator() (evaluator.ID, []string, error) {
	invalidId := evaluator.ID("")
	uuidGen, err := util.NewUUID()
	if err != nil {
		return invalidId, nil, err
	}
	threadsIDs, err := generateUUID(b.config.ThreadsPerWorker)
	if err != nil {
		return invalidId, nil, err
	}

	evaluatorId := evaluator.ID(uuidGen.Str())
	args := []string{
		b.notificationPort.ToString(),
		string(evaluatorId),
		strconv.Itoa(int(b.config.ThreadsPerWorker)),
	}
	for i := 0; i < len(threadsIDs); i++ {
		args = append(args, threadsIDs[i])
	}

	evaluatorProcess, err := process.NewProcess(evaluatorPath, args)
	if err != nil {
		return invalidId, nil, err
	}

	b.evaluators = append(b.evaluators, evaluatorProcess)
	return evaluatorId, threadsIDs, nil
}

func generateUUID(qty uint32) ([]string, error) {
	var uuids []string
	for i := uint32(0); i < qty; i++ {
		uuidGen, err := util.NewUUID()
		if err != nil {
			return nil, err
		}
		uuids = append(uuids, uuidGen.Str())
	}
	return uuids, nil
}

// TODO : Monitor process and spawn it back up if it crashes
