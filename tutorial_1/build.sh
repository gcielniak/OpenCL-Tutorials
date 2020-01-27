#!/usr/bin/env bash
mkdir build
cd build/
cmake ..
make
./tut1
cd ..
rm -r build/
