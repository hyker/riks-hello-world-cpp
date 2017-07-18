#!/bin/bash

if [[ -z $1 ]]; then
    echo "Must specify tag and platform."
    echo "Usage: ./build.sh <tag> <platform>"
    exit 1
fi
if [[ -z $2 ]]; then
    echo "Must specify platform."
    echo "Usage: ./build.sh <tag> <platform>"
    exit 1
fi

rm -rf build
mkdir build
cd build

python ../download.py $2 $1 .

g++ -L. -Iinclude ../main.cpp -lriks -o main.o -Wl,-rpath,. -std=c++11

cp ../res/default.config .
cp ../res/truststore.p12 .

echo
echo "Build complete. Running hello world..."
echo

./main.o
