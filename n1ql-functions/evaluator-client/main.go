package main

import "github.com/couchbase/eventing/n1ql-functions/evaluator-client/client"

func main() {
	client.NewEvaluator(client.Configuration{
		WorkersPerNode: 2,
		ThreadsPerWorker: 10,
		NsServerUrl: "http://locahost:9000",
	})
}
