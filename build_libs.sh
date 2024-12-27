#!/bin/bash

if [[ "$(uname)" == "Darwin" ]]; then
    echo "Running on macOS"



    cmake -GNinja -B build/debug/jolt  -DCMAKE_INSTALL_PREFIX=./lib/debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" ext/jolt/build -DTARGET_UNIT_TESTS=OFF -DTARGET_HELLO_WORLD=OFF -DTARGET_PERFORMANCE_TEST=OFF -DTARGET_SAMPLES=OFF -DTARGET_VIEWER=OFF
    cmake --build build/debug/jolt --config Debug
    cmake --install build/debug/jolt --config Debug 


else
# -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES="arm64"  -DSLANG_ENABLE_REPLAYER=OFF  
#-DSLANG_ENABLE_EXAMPLES=OFF
#-DSLANG_ENABLE_GFX=OFF
#-DSLANG_ENABLE_TESTS=OFF 
   echo "Not Running on macOS"
 
fi

