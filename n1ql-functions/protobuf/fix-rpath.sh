#!/usr/bin/env bash

GRPC_BUILD_DIR=/Users/gautham/projects/github/grpc/libs/opt/

for grpc_lib in `ls ${GRPC_BUILD_DIR}*.dylib`; do
    # Ensure any gRPC dependent libraries are corrected as well
    for dep_lib in $(otool -L ${grpc_lib} | awk 'NR > 3 {print $1}' | grep '^lib'); do
#        install_name_tool -change ${dep_lib} @rpath/${dep_lib} ${grpc_lib}
        install_name_tool -change ${dep_lib} ${GRPC_BUILD_DIR}${dep_lib} ${grpc_lib}
    done
done