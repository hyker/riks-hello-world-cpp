#!/bin/bash

rm -rf build
mkdir build
cd build

g++ -L../../riks-cpp/build -I../../riks-cpp/src ../main.cpp -lriks -o main.o -Wl,-rpath,../../riks-cpp/build -pthread -std=c++11

cp ../res/default.config .
cp ../res/root_certificate.pem .

echo
echo "Build complete. Running hello world..."
echo

./main.o
