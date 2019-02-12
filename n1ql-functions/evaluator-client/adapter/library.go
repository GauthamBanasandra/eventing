package adapter

import (
	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/util"
)

// TODO : Rename this to Library

type Library struct {
	Name string `json:"name"`
	ID   string `json:"id"`
	Code string `json:"code"`
}

func NewEmptyLibrary() (*Library, error) {
	uuidGen, err := util.NewUUID()
	if err != nil {
		return nil, err
	}
	return &Library{
		ID: uuidGen.Str(),
	}, nil
}

func NewLibrary(name, code string) (*Library, error) {
	library, err := NewEmptyLibrary()
	if err != nil {
		return nil, err
	}
	library.Name = name
	library.Code = code
	return library, nil
}

func (f *Library) ToNFTP() *nftp.Library {
	return &nftp.Library{
		ID:   f.ID,
		Code: f.Code,
	}
}
