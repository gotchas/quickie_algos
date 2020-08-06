#!/usr/bin/env sh
set -ex

THIS_DIR=$(realpath $(dirname $0))

rm -rf $THIS_DIR/build
mkdir $THIS_DIR/build

cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -H$THIS_DIR -B$THIS_DIR/build -G Ninja -DHUNTER_STATUS_DEBUG=ON -DCMAKE_CXX_COMPILER:FILEPATH=g++-10 # -DCMAKE_PROJECT_INCLUDE_BEFORE:STRING=$THIS_DIR/SetupHunter.cmake
# -DCMAKE_C_COMPILER:FILEPATH=/bin/clang-10 -DCMAKE_CXX_COMPILER:FILEPATH=/bin/clang++-10

cmake --build $THIS_DIR/build --config Debug --target all -- -j 10

cd $THIS_DIR/build
# the following option does notwork with target test:  --build $THIS_DIR/build
ctest --build $THIS_DIR/build --config Debug --target test --output-on-failure -- -j 10
cd ..
