package client

import (
	"context"
	"github.com/couchbase/eventing/gen/nftp/client"
	"google.golang.org/grpc"
	"log"
	"net"
)

type notificationServer struct {
	handle net.Listener
	stop   chan struct{}
}

func NewNotificationServer() (*notificationServer, error) {
	handle, err := net.Listen("tcp", "127.0.0.1:0")
	if err != nil {
		return nil, err
	}

	server := grpc.NewServer()
	nftp.RegisterNotificationServer(server, &notificationServer{
		handle: handle,
	})

	notificationServerInstance := &notificationServer{
		handle: handle,
		stop:   make(chan struct{}),
	}

	go server.Serve(handle)
	go notificationServerInstance.controller()
	return notificationServerInstance, nil
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
	log.Printf("Received port %v for evaluator %v", port.Port, port.EvaluatorId)
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
