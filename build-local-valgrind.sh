#!/bin/bash

rm -rf build
mkdir build
cd build

g++ -L../../riks-cpp/build -I../../riks-cpp/include ../main.cpp -lriks -o main.o -Wl,-rpath,../../riks-cpp/build -pthread -std=c++11

cp ../res/default.config .
cp ../res/truststore.p12 .

echo
echo "Build complete. Running hello world..."
echo

valgrind --tool=memcheck --leak-check=full -v ./main.o
