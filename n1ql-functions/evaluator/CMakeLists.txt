# Copyright (c) 2017 Couchbase, Inc.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#     http://www.apache.org/licenses/LICENSE-2.0
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an "AS IS"
# BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
# or implied. See the License for the specific language governing
# permissions and limitations under the License.

PROJECT(evaluator)

INCLUDE (FindCouchbaseV8)

SET(GRPC_BUILD_DIR
        /Users/gautham/projects/github/grpc)
SET(GEN_DIR
        ../../gen)
SET(LIBS_DIR
        ../../libs)

SET(LIB_GRPC
#        ${GRPC_BUILD_DIR}/libs/opt/libaddress_sorting.dylib
        ${GRPC_BUILD_DIR}/libs/opt/libgpr.dylib
        ${GRPC_BUILD_DIR}/libs/opt/libgrpc++.dylib
        ${GRPC_BUILD_DIR}/libs/opt/libgrpc++_cronet.dylib
#        ${GRPC_BUILD_DIR}/libs/opt/libgrpc++_error_details.dylib
        ${GRPC_BUILD_DIR}/libs/opt/libgrpc++_reflection.dylib
        ${GRPC_BUILD_DIR}/libs/opt/libgrpc++_unsecure.dylib
        ${GRPC_BUILD_DIR}/libs/opt/libgrpc.dylib
        ${GRPC_BUILD_DIR}/libs/opt/libgrpc_cronet.dylib
        ${GRPC_BUILD_DIR}/libs/opt/libgrpc_unsecure.dylib
#        ${GRPC_BUILD_DIR}/libs/opt/libgrpcpp_channelz.dylib
        ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotobuf-lite.17.dylib
        ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotobuf-lite.dylib
        ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotobuf.17.dylib
        ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotobuf.dylib
        ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotoc.17.dylib
        ${GRPC_BUILD_DIR}/third_party/protobuf/src/.libs/libprotoc.dylib)

SET(NFTP_SRC
        ${GEN_DIR}/nftp/server/evaluator.grpc.pb.cc
        ${GEN_DIR}/nftp/server/evaluator.pb.cc)

INCLUDE_DIRECTORIES(
        include
        ${GRPC_BUILD_DIR}/include
        ${GEN_DIR}/nftp/server
        ${V8_INCLUDE_DIR}
        ${LIBS_DIR}/include)

ADD_EXECUTABLE(evaluator
        ${NFTP_SRC}
        src/main.cc
        src/evaluator-server.cc
        src/evaluator.cc
        src/notification-client.cc)

TARGET_LINK_LIBRARIES(evaluator
        ${LIB_GRPC}
        ${V8_LIBRARIES})