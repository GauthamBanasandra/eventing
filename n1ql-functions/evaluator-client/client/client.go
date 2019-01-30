package client

import (
	"context"
	"errors"
	"log"

	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/babysitter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/server"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/configuration"
)

type EvaluatorClient struct {
	Babysitter         *babysitter.Babysitter
	NotificationServer *notificationServer

	evaluators         map[evaluator.ID]*evaluator.Evaluator
	appServer          *server.Server
	config             *configuration.Configuration
}

func NewEvaluatorClient(config *configuration.Configuration) (*EvaluatorClient, error) {
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
	evaluatorInstance.spawnAppServer()
	return evaluatorInstance, nil
}

func (e *EvaluatorClient) spawnAppServer() {
	e.appServer = server.NewServer(":" + e.config.HttpPort.ToString())
	go e.appServer.Start()
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

	e.Babysitter, err = babysitter.New(e.config, notificationPort)
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

// TODO : This isn't robust. If the first one succeeds and second one fails,
// the second one will never succeed upon calling Destroy() again
func (e *EvaluatorClient) Destroy() error {
	if err := e.appServer.Stop(); err != nil {
		return err
	}
	if err := e.NotificationServer.Stop(); err != nil {
		return err
	}
	return nil
}
