package client

import (
	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
)

type Configuration struct {
	WorkersPerNode   uint32
	ThreadsPerWorker uint32
	NsServerUrl      string
	HttpPort         port.Port
	DebuggerPort     port.Port
}

func (c *Configuration) ToNftp() *nftp.Config {
	return &nftp.Config{
		WorkersPerNode:   c.WorkersPerNode,
		ThreadsPerWorker: c.ThreadsPerWorker,
		NsServerUrl:      c.NsServerUrl,
	}
}
