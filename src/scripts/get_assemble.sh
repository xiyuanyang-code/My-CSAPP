#!/bin/bash

set -e

SOURCE_FILE="${1:-src/Lecture5/compile/pointer.c}"
OUTPUT_FILE="${SOURCE_FILE%.c}.s"

if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: Source file '$SOURCE_FILE' not found"
    exit 1
fi

OS_TYPE=$(uname -s)

echo "Generating assembly code for $SOURCE_FILE -> $OUTPUT_FILE"

case "$OS_TYPE" in
    Darwin)
        echo "Detected macOS, using clang..."
        clang -S \
            --target=x86_64-apple-macos \
            -fno-asynchronous-unwind-tables \
            "$SOURCE_FILE" \
            -o "$OUTPUT_FILE"
        ;;
    Linux)
        echo "Detected Linux, using gcc..."
        gcc -S \
            -masm=intel \
            -fno-asynchronous-unwind-tables \
            "$SOURCE_FILE" \
            -o "$OUTPUT_FILE"
        ;;
    *)
        echo "Error: Unsupported operating system: $OS_TYPE"
        exit 1
        ;;
esac

echo "Successfully generated $OUTPUT_FILE"

# * For compile optimizations, use -O1 flags:
# clang -S \
#     # -O1 \
#     --target=x86_64-apple-macos \
#     -fno-asynchronous-unwind-tables \
#     "$SOURCE_FILE" \
#     -o "$OUTPUT_FILE"
