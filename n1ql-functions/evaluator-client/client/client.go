package client

import (
	"context"
	"errors"
	"log"

	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/babysitter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/server"
)

type EvaluatorClient struct {
	Babysitter         *babysitter.Babysitter
	NotificationServer *notificationServer

	evaluators map[evaluator.ID]*evaluator.Evaluator
	scheduler  *Scheduler
	appServer  *server.Server
	config     *adapter.Configuration
}

func NewEvaluatorClient(config *adapter.Configuration) (*EvaluatorClient, error) {
	evaluatorInstance := &EvaluatorClient{
		config:     config,
		evaluators: make(map[evaluator.ID]*evaluator.Evaluator),
		scheduler:  NewScheduler(config.ThreadsPerWorker * config.WorkersPerNode),
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
		evaluatorID, threadIDs, err := e.Babysitter.AddEvaluator()
		if err != nil {
			return err
		}

		evaluatorPort := e.NotificationServer.WaitForEvaluatorPort(evaluatorID)

		evaluatorInstance, err := evaluator.New(evaluatorID, evaluatorPort)
		if err != nil {
			return err
		}
		e.scheduler.AddResources(threadIDs, evaluatorInstance)

		response, err := evaluatorInstance.Client.Initialize(context.Background(),
			e.config.ToNFTP())
		if err != nil {
			return err
		}
		log.Printf("Reponse : %s\t%v", evaluatorID, response)
		e.evaluators[evaluatorID] = evaluatorInstance
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

func (e *EvaluatorClient) AddFunction(f *adapter.Function) error {
	for _, evaluatorInstance := range e.evaluators {
		info, err := evaluatorInstance.Client.AddFunction(context.Background(), f.ToNFTP())
		log.Printf("Got response : %v", info)
		if err != nil {
			return err
		}
		if info.IsFatal {
			return errors.New(info.Message)
		}
	}
	return nil
}

func (e *EvaluatorClient) Evaluate(f *adapter.Function) error {
	res := <-e.scheduler.Resources
	defer func() {
		e.scheduler.Resources <- res
	}()

	info, err := res.evaluatorInstance.Client.Evaluate(context.Background(), &nftp.EvaluateRequest{
		FunctionID:   f.ID,
		FunctionName: "f",
		ThreadID:     res.threadID,
	})
	if err != nil {
		return err
	}
	if info.IsFatal {
		return errors.New(info.Message)
	}
	log.Printf("Got response : %v\t%v", res.threadID, info.Message)
	return nil
}
