#!/bin/bash
cd build
cmake .. && make
echo "--------------------"
cd ../
./build/potter