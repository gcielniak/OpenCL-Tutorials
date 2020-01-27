#!/usr/bin/env bash
mkdir -p build
cd build/
cmake ..
make
./tut1
cd ..
rm -r build/
