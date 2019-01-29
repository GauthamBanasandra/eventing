package client

import (
	"context"
	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/evaluator"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/port"
	"google.golang.org/grpc"
	"net"
)

type portNotification struct {
	evaluatorPort map[evaluator.ID]port.Port
	notification  chan struct{}
}

func newPortNotification() *portNotification {
	return &portNotification{
		evaluatorPort: make(map[evaluator.ID]port.Port),
		notification:  make(chan struct{}),
	}
}

type notificationServer struct {
	handle      net.Listener
	stop        chan struct{}
	portHandler *portNotification
}

func NewNotificationServer() (*notificationServer, error) {
	handle, err := net.Listen("tcp", "127.0.0.1:0")
	if err != nil {
		return nil, err
	}

	serverInstance := &notificationServer{
		handle:      handle,
		stop:        make(chan struct{}),
		portHandler: newPortNotification(),
	}

	server := grpc.NewServer()
	nftp.RegisterNotificationServer(server, serverInstance)

	go server.Serve(handle)
	go serverInstance.controller()
	return serverInstance, nil
}

func (n *notificationServer) Close() error {
	return n.handle.Close()
}

func (n *notificationServer) Port() (port.Port, error) {
	_, p, err := net.SplitHostPort(n.handle.Addr().String())
	if err != nil {
		return port.NewFromUInt32(0), err
	}
	return port.NewFromString(p)
}

func (n *notificationServer) NotifyPort(ctx context.Context, p *nftp.Port) (*nftp.Void, error) {
	n.portHandler.evaluatorPort[evaluator.ID(p.EvaluatorId)] = port.NewFromUInt32(p.Port)
	n.portHandler.notification <- struct{}{}
	return &nftp.Void{}, nil
}

func (n *notificationServer) controller() {
	for {
		select {
		case <-n.stop:
			n.handle.Close()
			return
		}
	}
}

func (n *notificationServer) WaitForEvaluatorPort(evaluatorId evaluator.ID) port.Port {
	for {
		if p, exists := n.portHandler.evaluatorPort[evaluatorId]; exists {
			return p
		}
		<-n.portHandler.notification
	}
}
