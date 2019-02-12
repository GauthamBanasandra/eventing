package adapter

import (
	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/util"
)

// TODO : Rename this to Library

type Function struct {
	Name string `json:"name"`
	ID   string `json:"id"`
	Code string `json:"code"`
}

func NewEmptyFunction() (*Function, error) {
	uuidGen, err := util.NewUUID()
	if err != nil {
		return nil, err
	}
	return &Function{
		ID: uuidGen.Str(),
	}, nil
}

func NewFunction(name, code string) (*Function, error) {
	function, err := NewEmptyFunction()
	if err != nil {
		return nil, err
	}
	function.Name = name
	function.Code = code
	return function, nil
}

func (f *Function) ToNFTP() *nftp.Function {
	return &nftp.Function{
		ID:   f.ID,
		Code: f.Code,
	}
}
