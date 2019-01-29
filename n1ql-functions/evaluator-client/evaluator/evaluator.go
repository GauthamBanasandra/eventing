package evaluator

import (
	"fmt"

	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"google.golang.org/grpc"
)

type ID string

type Evaluator struct {
	EvaluatorID ID
	Client      nftp.EvaluatorClient
}

func New(evaluatorId ID, evaluatorPort port.Port) (*Evaluator, error) {
	var options []grpc.DialOption
	options = append(options, grpc.WithInsecure())

	connection, err := grpc.Dial(fmt.Sprintf("127.0.0.1:%v", evaluatorPort), options...)
	if err != nil {
		return nil, err
	}
	return &Evaluator{
		EvaluatorID: evaluatorId,
		Client:      nftp.NewEvaluatorClient(connection),
	}, nil
}
