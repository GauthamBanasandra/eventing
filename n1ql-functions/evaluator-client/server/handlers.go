package server

import (
	"fmt"
	"log"
	"net/http"

	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
)

func (s *Server) functionsHandler(w http.ResponseWriter, r *http.Request) {
	code := `
		function f(){
			let value = 2 + 2;
			return value;
		}
		f();`
	function, err := adapter.NewFunction(code)
	if err != nil {
		log.Fatalf("Unable to create Function, err : %v", err)
	}

	switch r.Method {
	case "POST":
		s.storage.AddFunction(function)
	}
	fmt.Fprint(w, "Hello")
}
