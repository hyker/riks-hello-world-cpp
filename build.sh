#!/bin/bash

g++ -Ldeps -Ideps/include main.cpp -lriks -lssl -lcrypto -o main.o -Wl,-rpath,deps -std=c++11
