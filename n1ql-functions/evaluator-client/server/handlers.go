package server

import (
	"fmt"
	"net/http"
)

func functionsHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, "Hello")
}
