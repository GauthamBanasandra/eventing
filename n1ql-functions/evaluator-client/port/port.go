package port

import "strconv"

type Port uint32

func NewFromString(port string) (Port, error) {
	p, err := strconv.Atoi(port)
	if err != nil {
		return Port(0), err
	}
	return Port(p), nil
}

func NewFromUInt32(port uint32) Port {
	return Port(port)
}

func (p *Port) ToString() string {
	return strconv.Itoa(int(*p))
}
