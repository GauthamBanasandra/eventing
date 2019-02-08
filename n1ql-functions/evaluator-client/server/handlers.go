package server

import (
	"fmt"
	"log"
	"net/http"

	"encoding/json"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"io/ioutil"
)

func (s *Server) functionsHandler(w http.ResponseWriter, r *http.Request) {
	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		log.Printf("error in reading body : %v", err)
		return
	}

	switch r.Method {
	case "POST":
		function, err := adapter.NewEmptyFunction()
		if err != nil {
			log.Printf("error in creating empty function : %v", err)
			return
		}
		err = json.Unmarshal(body, function)
		if err != nil {
			log.Printf("error in unmarshalling json : %v", err)
			return
		}
		err = s.storage.AddFunction(function)
		if err != nil {
			log.Printf("error in writing to metakv, err : %v", err)
		}
	}
	fmt.Fprint(w, "Hello")
}
