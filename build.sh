#!/usr/bin/bash

echo "removing build folder"
rm -rf build
echo "building..."
mkdir build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake --build .