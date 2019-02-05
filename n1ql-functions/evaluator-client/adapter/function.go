package adapter

import (
	"github.com/couchbase/eventing/gen/nftp/client"
	"github.com/couchbase/eventing/util"
)

type Function struct {
	ID   string
	Code string
}

func NewFunction(code string) (*Function, error) {
	uuidGen, err := util.NewUUID()
	if err != nil {
		return nil, err
	}
	return &Function{
		ID:   uuidGen.Str(),
		Code: code,
	}, nil
}

func (f *Function) ToNFTP() *nftp.Function {
	return &nftp.Function{
		ID:   f.ID,
		Code: f.Code,
	}
}
