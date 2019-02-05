package main

import (
	"bufio"
	"log"
	"os"

	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"strings"
)

func main() {
	evaluatorClient, err := client.NewEvaluatorClient(&adapter.Configuration{
		WorkersPerNode:   2,
		ThreadsPerWorker: 3,
		HttpPort:         port.Port(9090),
		NsServerUrl:      "http://locahost:9000",
	})
	if err != nil {
		log.Fatalf("Unable to start evaluator client, err : %v", err)
	}

	code := `
		function f(){
			let value = 2 + 2;
			return value;
		}
		f();`
	f, err := adapter.NewFunction(code)
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
			if err := evaluatorClient.AddFunction(f); err != nil {
				log.Fatalf("Unable to add Function, err : %v", err)
			}

		case "eval":
			for i := 0; i < 10; i++ {
				go func() {
					if err := evaluatorClient.Evaluate(f); err != nil {
						log.Fatalf("Unable to evaluate, err : %v", err)
					}
				}()
			}
		}
	}
}
