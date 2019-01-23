package server

import "net/http"

type Server struct {
	hostAddress string
}

func NewServer(hostAddress string) *Server {
	return &Server{
		hostAddress: hostAddress,
	}
}

func (s *Server) Start() error {
	http.HandleFunc("/api/v1/functions", functionsHandler)
	http.HandleFunc("/api/v1/functions/", functionsHandler)
	return http.ListenAndServe(s.hostAddress, nil)
}
