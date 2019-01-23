#!/usr/bin/env bash

EXECUTABLE=/Users/gautham/projects/github/couchbase/mad-hatter/cmake-build-debug/goproj/src/github.com/couchbase/eventing/n1ql-functions/evaluator/evaluator
GRPC_BUILD_DIR=/Users/gautham/projects/github/grpc

install_name_tool -change libgpr.dylib ${GRPC_BUILD_DIR}/libs/opt/libgpr.dylib ${EXECUTABLE}
install_name_tool -change libaddress_sorting.dylib ${GRPC_BUILD_DIR}/libs/opt/libaddress_sorting.dylib ${EXECUTABLE}
install_name_tool -change libgrpc++.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpc++.dylib ${EXECUTABLE}
install_name_tool -change libgrpc++_cronet.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpc++_cronet.dylib ${EXECUTABLE}
install_name_tool -change libgrpc++_error_details.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpc++_error_details.dylib ${EXECUTABLE}
install_name_tool -change libgrpc++_reflection.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpc++_reflection.dylib ${EXECUTABLE}
install_name_tool -change libgrpc++_unsecure.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpc++_unsecure.dylib ${EXECUTABLE}
install_name_tool -change libgrpc.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpc.dylib ${EXECUTABLE}
install_name_tool -change libgrpc_cronet.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpc_cronet.dylib ${EXECUTABLE}
install_name_tool -change libgrpc_unsecure.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpc_unsecure.dylib ${EXECUTABLE}
install_name_tool -change libgrpcpp_channelz.dylib ${GRPC_BUILD_DIR}/libs/opt/libgrpcpp_channelz.dylib ${EXECUTABLE}
install_name_tool -change libprotobuf-lite.17.dylib ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotobuf-lite.17.dylib ${EXECUTABLE}
install_name_tool -change libprotobuf-lite.dylib ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotobuf-lite.dylib ${EXECUTABLE}
install_name_tool -change libprotobuf.17.dylib ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotobuf.17.dylib ${EXECUTABLE}
install_name_tool -change libprotobuf.dylib ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotobuf.dylib ${EXECUTABLE}
install_name_tool -change libprotoc.17.dylib ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotoc.17.dylib ${EXECUTABLE}
install_name_tool -change libprotoc.dylib ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotoc.dylib ${EXECUTABLE}