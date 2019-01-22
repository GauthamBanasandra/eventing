package main

import (
	"fmt"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/client"
)

func main() {
	_, err := client.NewEvaluator(client.Configuration{
		WorkersPerNode:   2,
		ThreadsPerWorker: 10,
		NsServerUrl:      "http://locahost:9000",
	})
	if err != nil {
		fmt.Printf("Error main, err : %v\n", err)
	}
}
