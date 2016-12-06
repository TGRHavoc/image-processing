#!/bin/bash

echo "Starting..."

# Make sure "output" exists..
if [ ! -d "output/" ]; then
    mkdir output/
fi

# Compile the program !!
g++ -std=c++14 -w *.cpp *.h -o output/a.out

echo "Done"
