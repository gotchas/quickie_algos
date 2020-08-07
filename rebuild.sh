#!/usr/bin/env bash
set -ex

THIS_DIR=$(realpath $(dirname $0))

rm -rf $THIS_DIR/build

BUILD_TYPE=Release
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=$BUILD_TYPE -H$THIS_DIR -B$THIS_DIR/build -DHUNTER_STATUS_DEBUG=ON -DCMAKE_CXX_COMPILER:FILEPATH=g++-10 
# -DCMAKE_PROJECT_INCLUDE_BEFORE:STRING=$THIS_DIR/SetupHunter.cmake

cmake --build $THIS_DIR/build --config $BUILD_TYPE --target all -- -j 10

cd $THIS_DIR/build
# the following option does notwork with target test:  --build $THIS_DIR/build
ctest --build $THIS_DIR/build --config $BUILD_TYPE --target test --output-on-failure -- -j 10
cd ..
