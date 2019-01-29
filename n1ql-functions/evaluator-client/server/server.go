package server

import (
	"log"
	"net/http"
)

type Server struct {
	server *http.Server
}

func NewServer(hostAddress string) *Server {
	http.HandleFunc("/api/v1/functions", functionsHandler)
	http.HandleFunc("/api/v1/functions/", functionsHandler)
	return &Server{
		server: &http.Server{Addr: hostAddress},
	}
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
