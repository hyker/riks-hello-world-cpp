#!/bin/bash

#rm -rf build
mkdir -p build
cd build

conan install ../../riks-cpp -s build_type=Debug -s compiler=gcc -s compiler.libcxx=libstdc++11 -s arch=x86_64 --build missing
cmake .. -G "Unix Makefiles"
cmake --build . --config Debug

cp ../res/default.config .
cp ../res/root_certificate.pem .

echo
echo "Build complete. Running hello world..."
echo

valgrind --tool=memcheck --leak-check=full --track-origins=yes -v ./bin/riks
