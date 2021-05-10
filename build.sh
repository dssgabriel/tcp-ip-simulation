#!/bin/sh

mkdir -p build/
cd build
cmake ..
make
./Sim-TCP_IP
