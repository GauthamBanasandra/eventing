package server

import (
	"log"
	"net/http"

	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/storage"
)

type Server struct {
	server  *http.Server
	storage *storage.Storage
}

func NewServer(hostAddress string, storageInstance *storage.Storage) *Server {
	s := &Server{
		server:  &http.Server{Addr: hostAddress},
		storage: storageInstance,
	}
	http.HandleFunc("/api/v1/functions", s.librariesHandler)
	http.HandleFunc("/api/v1/functions/", s.librariesHandler)
	return s
}

func (s *Server) Start() {
	err := s.server.ListenAndServe()
	if err != nil && err != http.ErrServerClosed {
		log.Fatalf("Unable to start HTTP server, err : %v", err)
	}
}

func (s *Server) Stop() error {
	return s.server.Shutdown(nil)
}
