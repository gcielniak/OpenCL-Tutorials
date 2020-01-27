#!/usr/bin/env bash
rm -r build/
mkdir -p build
cd build/
cmake ..
make
./tut1
cd ..
