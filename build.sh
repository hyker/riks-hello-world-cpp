#!/bin/bash

g++ -Ldeps -Ideps/include main.cpp -lriks -o main.o -Wl,-rpath,deps -std=c++11