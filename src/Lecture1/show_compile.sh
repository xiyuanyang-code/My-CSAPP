#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 hello.c"
    exit 1
fi

SOURCE_FILE=$1
BASE_NAME=$(basename "$SOURCE_FILE" .c)
SOURCE_DIR=$(dirname "$SOURCE_FILE")

# create compile directory
COMPILE_DIR="${SOURCE_DIR}/compile"
mkdir -p "$COMPILE_DIR"

# stage 1: preprocessing
gcc -E "$SOURCE_FILE" -o "${COMPILE_DIR}/${BASE_NAME}.i"

# stage 2: compilation
gcc -S "${COMPILE_DIR}/${BASE_NAME}.i" -o "${COMPILE_DIR}/${BASE_NAME}.s"

# stage 3: assembly
gcc -c "${COMPILE_DIR}/${BASE_NAME}.s" -o "${COMPILE_DIR}/${BASE_NAME}.o"

# stage 4: linking
gcc "${COMPILE_DIR}/${BASE_NAME}.o" -o "${COMPILE_DIR}/${BASE_NAME}"

echo "Compilation artifacts generated in: $COMPILE_DIR"
ls -l "${COMPILE_DIR}/${BASE_NAME}"*