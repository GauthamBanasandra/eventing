package client

import (
	"errors"

	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/babysitter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/server"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/storage"
)

type EvaluatorClient struct {
	Babysitter         *babysitter.Babysitter
	NotificationServer *notificationServer

	evaluators chan *evaluator.Evaluator // TODO : Turn this into a channel
	scheduler  *Scheduler
	storage    *storage.Storage
	appServer  *server.Server
	config     *adapter.Configuration
}

func NewEvaluatorClient(config *adapter.Configuration) (*EvaluatorClient, error) {
	evaluatorInstance := &EvaluatorClient{
		config:     config,
		evaluators: make(chan *evaluator.Evaluator, config.WorkersPerNode),
		scheduler:  NewScheduler(config),
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
	address := ":" + e.config.HttpPort.ToString()
	e.appServer = server.NewServer(address, e.storage)
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
	e.storage = storage.New(e.AddFunction)
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

		// TODO : Remove this
		err = evaluatorInstance.Initialize(e.config)
		if err != nil {
			return err
		}
		e.evaluators <- evaluatorInstance
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
	e.scheduler.FreeResources()
	//for _, evaluatorInstance := range e.evaluators {
	//	go evaluatorInstance.Destroy()
	//}
	return nil
}

func (e *EvaluatorClient) AddFunction(f *adapter.Function) error {
	var evaluators []*evaluator.Evaluator
	defer func() {
		for i := 0; i < len(evaluators); i++ {
			e.evaluators <- evaluators[i]
		}
	}()

	for i := uint32(0); i < e.config.WorkersPerNode; i++ {
		evaluatorInstance := <-e.evaluators
		err := evaluatorInstance.AddFunction(f)
		evaluators = append(evaluators, evaluatorInstance)
		if err != nil {
			return err
		}
	}
	return nil
}

func (e *EvaluatorClient) Evaluate(f *adapter.Function) (*string, error) {
	res := <-e.scheduler.Resources
	defer func() {
		e.scheduler.Resources <- res
	}()

	return res.evaluatorInstance.Evaluate(&nftp.EvaluateRequest{
		FunctionID:   f.ID,
		FunctionName: "f",
		ThreadID:     res.threadID,
	})
}
