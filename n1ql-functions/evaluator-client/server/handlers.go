package server

import (
	"log"
	"net/http"

	"encoding/json"
	"github.com/couchbase/eventing/n1ql-functions/evaluator-client/adapter"
	"io/ioutil"
)

func (s *Server) librariesHandler(w http.ResponseWriter, r *http.Request) {
	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		log.Printf("error in reading body : %v", err)
		return
	}

	switch r.Method {
	case "POST":
		library, err := adapter.NewEmptyLibrary()
		if err != nil {
			log.Printf("error in creating empty function : %v", err)
			return
		}
		err = json.Unmarshal(body, library)
		if err != nil {
			log.Printf("error in unmarshalling json : %v", err)
			return
		}
		err = s.storage.AddLibrary(library)
		if err != nil {
			log.Printf("error in writing to metakv, err : %v", err)
		}

	case "GET":
		// TODO : Handle retrieval of Libraries

	case "DELETE":
		// TODO : Handle deletion of Libraries
	}
}
