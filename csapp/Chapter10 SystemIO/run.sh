#!/bin/bash
cd build
cmake .. && make
echo "--------------------"
cd ../
./build/potter 64.12.149.13

