package process

import (
	"io"
	"os/exec"
)

type Process struct {
	handle  *exec.Cmd
	inPipe  io.WriteCloser
	outPipe io.ReadCloser
	errPipe io.ReadCloser
}

func NewProcess(executablePath string, args []string) (*Process, error) {
	handle := exec.Command(executablePath, args...)
	inPipe, err := handle.StdinPipe()
	if err != nil {
		return nil, err
	}

	outPipe, err := handle.StdoutPipe()
	if err != nil {
		return nil, err
	}

	errPipe, err := handle.StderrPipe()
	if err != nil {
		return nil, err
	}

	err = handle.Start()
	if err != nil {
		return nil, err
	}
	return &Process{
		handle:  handle,
		inPipe:  inPipe,
		outPipe: outPipe,
		errPipe: errPipe,
	}, nil
}

func (p *Process) CloseAllPipes() error {
	err := p.inPipe.Close()
	if err != nil {
		return err
	}

	err = p.outPipe.Close()
	if err != nil {
		return err
	}

	err = p.errPipe.Close()
	if err != nil {
		return err
	}

	return nil
}
