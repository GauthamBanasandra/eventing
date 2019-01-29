package client

import (
	"context"
	"errors"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/babysitter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/server"
	"log"
)

type EvaluatorClient struct {
	Babysitter         *babysitter.Babysitter
	NotificationServer *notificationServer

	evaluators map[evaluator.ID]*evaluator.Evaluator
	config     Configuration
}

func (e *EvaluatorClient) spawnComponents() error {
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

func (e *EvaluatorClient) spawnEvaluators() error {
	if e.Babysitter == nil {
		return errors.New("Babysitter is not initialized")
	}
	if e.NotificationServer == nil {
		return errors.New("NotificationServer is not initialized")
	}

	for i := uint32(0); i < e.config.WorkersPerNode; i++ {
		evaluatorId, err := e.Babysitter.AddEvaluator()
		if err != nil {
			return err
		}

		evaluatorPort := e.NotificationServer.WaitForEvaluatorPort(evaluatorId)

		evaluatorInstance, err := evaluator.New(evaluatorId, evaluatorPort)
		if err != nil {
			return err
		}

		response, err := evaluatorInstance.Client.Initialize(context.Background(),
			e.config.ToNftp())
		if err != nil {
			return err
		}
		log.Printf("Reponse : %s\t%v", evaluatorId, response)
		e.evaluators[evaluatorId] = evaluatorInstance
	}
	return nil
}

func NewEvaluatorClient(config Configuration) (*EvaluatorClient, error) {
	evaluatorInstance := &EvaluatorClient{
		config:     config,
		evaluators: make(map[evaluator.ID]*evaluator.Evaluator),
	}
	if err := evaluatorInstance.spawnComponents(); err != nil {
		return nil, err
	}
	if err := evaluatorInstance.spawnEvaluators(); err != nil {
		return nil, err
	}

	appServer := server.NewServer(":9080")
	err := appServer.Start()
	if err != nil {
		return nil, err
	}
	return evaluatorInstance, nil
}
