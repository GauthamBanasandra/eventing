package main

import (
	"bufio"
	"log"
	"os"
	"strings"

	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
)

func main() {
	evaluatorClient, err := client.NewEvaluatorClient(&adapter.Configuration{
		WorkersPerNode:   1,
		ThreadsPerWorker: 3,
		HttpPort:         port.Port(9090),
		NsServerUrl:      "http://locahost:9000",
	})
	if err != nil {
		log.Fatalf("Unable to start evaluator client, err : %v", err)
	}

	code := `
		function f(){
			throw 'some error';
			let value = 2 + 2;
			return value;
		}`
	f, err := adapter.NewLibrary("another-math", code)
	if err != nil {
		log.Fatalf("Unable to create Function, err : %v", err)
	}

	reader := bufio.NewReader(os.Stdin)
	for {
		command, err := reader.ReadString('\n')
		if err != nil {
			log.Fatalf("Unable to start evaluator client, err : %v", err)
		}
		command = strings.Replace(command, "\n", "", -1)
		switch command {
		case "stop":
			if err := evaluatorClient.Destroy(); err != nil {
				log.Fatalf("Unable to stop evaluator client, err : %v", err)
			}
			return

		case "add":
			if err := evaluatorClient.AddLibrary(f); err != nil {
				log.Fatalf("Unable to add Function, err : %v", err)
			}

		case "eval":
			args, err := reader.ReadString('\n')
			if err != nil {
				log.Fatalf("Unable to read eval args, err : %v", err)
			}
			args = strings.Replace(args, "\n", "", -1)
			evalArgs := strings.Split(args, " ")
			for i := 0; i < 10; i++ {
				go func() {
					result, err := evaluatorClient.Evaluate(evalArgs[0], evalArgs[1])
					if err != nil {
						log.Printf("Unable to evaluate, err : %v", err)
						return
					}
					log.Printf("Evaluate response : %v", *result)
				}()
			}
		}
	}
}
