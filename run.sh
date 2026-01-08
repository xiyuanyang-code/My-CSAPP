#!/bin/bash
file=$1
filename=$(basename "$file")
name="${filename%.*}"
extension="${filename##*.}"
mkdir -p ./build
    
    if [ "$extension" = "c" ]; then
        gcc -Wall -g "$file" -o "build/$name" && "./build/$name"
    elif [ "$extension" = "cpp" ]; then
        g++ -Wall -g "$file" -o "build/$name" && "./build/$name"
    fi
