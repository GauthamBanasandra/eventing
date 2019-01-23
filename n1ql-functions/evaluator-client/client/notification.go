package client

import (
	"context"
	"github.com/couchbase/eventing/gen/nftp/client"
	"google.golang.org/grpc"
	"net"
)

type portNotification struct {
	evaluatorPort map[string]uint32
	notification  chan struct{}
}

func newPortNotification() *portNotification {
	return &portNotification{
		evaluatorPort: make(map[string]uint32),
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

func (n *notificationServer) Port() (string, error) {
	_, port, err := net.SplitHostPort(n.handle.Addr().String())
	if err != nil {
		return "", err
	}
	return port, nil
}

func (n *notificationServer) NotifyPort(ctx context.Context, port *nftp.Port) (*nftp.Void, error) {
	n.portHandler.evaluatorPort[port.EvaluatorId] = port.Port
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

func (n *notificationServer) WaitForEvaluatorPort(evaluatorId string) uint32 {
	for {
		if port, exists := n.portHandler.evaluatorPort[evaluatorId]; exists {
			return port
		}
		<-n.portHandler.notification
	}
}
