package evaluator

import (
	"context"
	"errors"
	"fmt"
	"log"

	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"google.golang.org/grpc"
)

type ID string

type Evaluator struct {
	EvaluatorID ID
	client      nftp.EvaluatorClient
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
		client:      nftp.NewEvaluatorClient(connection),
	}, nil
}

func (e *Evaluator) Destroy() error {
	// TODO : Calling this was supposed to shutdown gRPC server
	// in evaluator, which isn't happening. Need to investigate.
	_, err := e.client.Stop(context.Background(), &nftp.Void{})
	if err != nil {
		return err
	}
	return nil
}

func (e *Evaluator) AddFunction(function *adapter.Function) error {
	info, err := e.client.AddFunction(context.Background(), function.ToNFTP())
	if err != nil {
		return err
	}
	if info.IsFatal {
		return errors.New(info.Message)
	}
	return nil
}

func (e *Evaluator) Evaluate(request *nftp.EvaluateRequest) (*string, error) {
	empty := ""
	info, err := e.client.Evaluate(context.Background(), request)
	if err != nil {
		return &empty, err
	}
	if info.IsFatal {
		return &empty, errors.New(info.Message)
	}
	return &info.Message, nil
}

func (e *Evaluator) Initialize(config *adapter.Configuration) error {
	response, err := e.client.Initialize(context.Background(), config.ToNFTP())
	if err != nil {
		return err
	}
	log.Printf("Reponse : %v", response)
	return nil
}
