package client

import (
	"github.com/couchbase/eventing/gen/nftp/client"
	"google.golang.org/grpc"
	"log"
	"golang.org/x/net/context"
)

type Evaluator struct {
	config          Configuration
	connection      *grpc.ClientConn
	evaluatorClient nftp.EvaluatorClient
}

type Configuration struct {
	WorkersPerNode   uint32
	ThreadsPerWorker uint32
	NsServerUrl      string
	HttpPort         string
	DebuggerPort     string
}

func (c *Configuration) ToNftp() *nftp.Config {
	return &nftp.Config{
		WorkersPerNode: c.WorkersPerNode,
		ThreadsPerWorker: c.ThreadsPerWorker,
		NsServerUrl: c.NsServerUrl,
	}
}

func NewEvaluator(config Configuration) (*Evaluator, error) {
	var options []grpc.DialOption
	options = append(options, grpc.WithInsecure())

	connection, err := grpc.Dial("127.0.0.1:9090", options...)
	if err != nil {
		log.Fatalf("Unable to connect to server : %v", err)
	}

	evaluatorClient := nftp.NewEvaluatorClient(connection)
	response, err := evaluatorClient.Initialize(context.Background(), config.ToNftp())
	if err != nil {
		return nil, err
	}

	log.Printf("Reponse : %v", response)

	evaluator := &Evaluator{
		config: config,
		connection: connection,
		evaluatorClient: evaluatorClient,
	}
	return evaluator, nil
}

func (e *Evaluator) Evaluate() {
}