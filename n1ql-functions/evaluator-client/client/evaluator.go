package client

import (
	"context"
	"errors"
	"fmt"
	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/babysitter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/server"
	"google.golang.org/grpc"
	"log"
)

type Evaluator struct {
	Babysitter         *babysitter.Babysitter
	NotificationServer *notificationServer

	config     Configuration
	connection *grpc.ClientConn
	client     nftp.EvaluatorClient
}

func (e *Evaluator) spawnComponents() error {
	var err error
	e.NotificationServer, err = NewNotificationServer()
	if err != nil {
		return err
	}

	notificationPort, err := e.NotificationServer.Port()
	if err != nil {
		return err
	}

	e.Babysitter, err = babysitter.New(notificationPort)
	if err != nil {
		return err
	}
	return nil
}

func (e *Evaluator) spawnEvaluators() error {
	if e.Babysitter == nil {
		return errors.New("Babysitter is not initialized")
	}
	if e.NotificationServer == nil {
		return errors.New("NotificationServer is not initialized")
	}

	evaluatorId, err := e.Babysitter.AddEvaluator()
	if err != nil {
		return err
	}

	evaluatorPort := e.NotificationServer.WaitForEvaluatorPort(evaluatorId)

	if err := e.initializeConnection(evaluatorPort); err != nil {
		return err
	}

	e.client = nftp.NewEvaluatorClient(e.connection)
	return nil
}

func (e *Evaluator) initializeConnection(evaluatorPort port.Port) error {
	var err error
	var options []grpc.DialOption
	options = append(options, grpc.WithInsecure())

	e.connection, err = grpc.Dial(fmt.Sprintf("127.0.0.1:%v", evaluatorPort), options...)
	if err != nil {
		return err
	}
	return nil
}

func NewEvaluator(config Configuration) (*Evaluator, error) {
	evaluator := &Evaluator{
		config: config,
	}
	if err := evaluator.spawnComponents(); err != nil {
		return nil, err
	}
	if err := evaluator.spawnEvaluators(); err != nil {
		return nil, err
	}

	response, err := evaluator.client.Initialize(context.Background(), config.ToNftp())
	if err != nil {
		return nil, err
	}
	log.Printf("Reponse : %v", response)

	appServer := server.NewServer(":9080")
	err = appServer.Start()
	if err != nil {
		return nil, err
	}
	return evaluator, nil
}
