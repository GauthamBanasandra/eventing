package client

import "github.com/couchbase/eventing/gen/nftp/client"

type Configuration struct {
	WorkersPerNode   uint32
	ThreadsPerWorker uint32
	NsServerUrl      string
	HttpPort         string
	DebuggerPort     string
}

func (c *Configuration) ToNftp() *nftp.Config {
	return &nftp.Config{
		WorkersPerNode:   c.WorkersPerNode,
		ThreadsPerWorker: c.ThreadsPerWorker,
		NsServerUrl:      c.NsServerUrl,
	}
}
