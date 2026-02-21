#!/bin/bash

INPUT_FILE="$1"
FILENAME_NODE="${INPUT_FILE%.*}"
OUTPUT_FILE="${FILENAME_NODE}.s"
gcc -Og -S -fno-if-conversion -fjump-tables "$INPUT_FILE" -o "$OUTPUT_FILE"
