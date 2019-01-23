#!/usr/bin/env bash

protoc -I ./protobuf --grpc_out=../gen/nftp/server/ --plugin=protoc-gen-grpc=/Users/gautham/projects/github/grpc/bins/opt/grpc_cpp_plugin ./protobuf/evaluator.proto
protoc -I ./protobuf --cpp_out=../gen/nftp/server/ ./protobuf/evaluator.proto
#protoc -I ./protobuf --go_out=plugins=grpc:../gen/nftp/client/ --plugin=protoc-gen-go=/Users/gautham/projects/github/grpc/third_party/protoc-gen-validate/vendor/github.com/golang/protobuf/protoc-gen-go/protoc-gen-go ./protobuf/evaluator.proto
protoc -I ./protobuf --go_out=plugins=grpc:../gen/nftp/client/ --plugin=protoc-gen-go=/Users/gautham/projects/github/couchbase/mad-hatter/godeps/src/github.com/golang/protobuf/protoc-gen-go/protoc-gen-go ./protobuf/evaluator.proto