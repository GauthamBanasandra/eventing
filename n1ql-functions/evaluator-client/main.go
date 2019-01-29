package main

import (
	"bufio"
	"log"
	"os"

	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"strings"
)

func main() {
	evaluatorClient, err := client.NewEvaluatorClient(client.Configuration{
		WorkersPerNode:   2,
		ThreadsPerWorker: 10,
		HttpPort:         port.Port(9090),
		NsServerUrl:      "http://locahost:9000",
	})
	if err != nil {
		log.Fatalf("Unable to start evaluator client, err : %v", err)
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
		}
	}
}
