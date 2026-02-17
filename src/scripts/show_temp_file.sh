#!/bin/bash

SOURCE_FILE="src/Lecture5/main.c"
MATH_TOOL_FILE="src/Lecture5/math_tool.c"
BASE_NAME=$(basename "$SOURCE_FILE" .c)
SOURCE_DIR=$(dirname "$SOURCE_FILE")

# create compile directory
COMPILE_DIR="${SOURCE_DIR}/compile"
mkdir -p "$COMPILE_DIR"

# optimization levels
OPT_LEVELS=("O0" "Og" "O1" "O2" "O3")
OPT_DESCRIPTIONS=(
  "Default level - No optimization, fastest compilation, best for debugging low-level logic"
  "Debug preferred - Enables optimizations that don't interfere with debugging"
  "Basic optimization - Slightly optimizes performance, ignores compilation time"
  "Release preferred - Enables almost all optimizations except space-time trade-offs"
  "Maximum performance - Heavy optimization with aggressive inlining, fastest but larger binary"
)

for i in "${!OPT_LEVELS[@]}"; do
  OPT_LEVEL="-${OPT_LEVELS[$i]}"
  OPT_DIR="${COMPILE_DIR}/${OPT_LEVELS[$i]}"
  mkdir -p "$OPT_DIR"

  echo "=========================================="
  echo "Optimization Level: $OPT_LEVEL"
  echo "${OPT_DESCRIPTIONS[$i]}"
  echo "=========================================="
  echo ""

  # stage 1: preprocessing
  echo "Stage 1: Preprocessing (.c -> .i)"
  gcc -E "$SOURCE_FILE" -o "${OPT_DIR}/${BASE_NAME}.i"
  gcc -E "$MATH_TOOL_FILE" -o "${OPT_DIR}/math_tool.i"

  echo "Preprocessed files:"
  ls -lh "${OPT_DIR}/"*.i
  echo ""
  echo "First 30 lines of preprocessed main.c:"
  head -n 30 "${OPT_DIR}/${BASE_NAME}.i"
  echo "..."
  echo ""

  # stage 2: compilation
  echo "Stage 2: Compilation (.i -> .s)"
  gcc -S "$OPT_LEVEL" "${OPT_DIR}/${BASE_NAME}.i" -o "${OPT_DIR}/${BASE_NAME}.s"
  gcc -S "$OPT_LEVEL" "${OPT_DIR}/math_tool.i" -o "${OPT_DIR}/math_tool.s"

  echo "Assembly files:"
  ls -lh "${OPT_DIR}/"*.s
  echo ""
  echo "First 30 lines of main assembly code:"
  head -n 30 "${OPT_DIR}/${BASE_NAME}.s"
  echo "..."
  echo ""

  # stage 3: assembly
  echo "Stage 3: Assembly (.s -> .o)"
  gcc -c "$OPT_LEVEL" "${OPT_DIR}/${BASE_NAME}.s" -o "${OPT_DIR}/${BASE_NAME}.o"
  gcc -c "$OPT_LEVEL" "${OPT_DIR}/math_tool.s" -o "${OPT_DIR}/math_tool.o"

  echo "Object files:"
  ls -lh "${OPT_DIR}/"*.o
  echo ""
  echo "Object file information:"
  file "${OPT_DIR}/${BASE_NAME}.o"
  file "${OPT_DIR}/math_tool.o"
  echo ""

  # stage 4: linking
  echo "Stage 4: Linking (.o -> executable)"
  gcc "$OPT_LEVEL" "${OPT_DIR}/${BASE_NAME}.o" "${OPT_DIR}/math_tool.o" \
    -o "${OPT_DIR}/${BASE_NAME}" -lm

  echo "Final executable:"
  ls -lh "${OPT_DIR}/${BASE_NAME}"
  echo ""
  echo "Executable file information:"
  file "${OPT_DIR}/${BASE_NAME}"
  echo ""

  echo "=========================================="
  echo "Size comparison for $OPT_LEVEL:"
  echo "=========================================="
  du -h "${OPT_DIR}/${BASE_NAME}.i" "${OPT_DIR}/${BASE_NAME}.s" \
       "${OPT_DIR}/${BASE_NAME}.o" "${OPT_DIR}/${BASE_NAME}"
  echo ""
  echo ""
done

echo "=========================================="
echo "Summary: All optimization levels"
echo "=========================================="
echo ""
echo "Executable sizes across optimization levels:"
for OPT in "${OPT_LEVELS[@]}"; do
  printf "%-5s: " "$OPT"
  ls -lh "${COMPILE_DIR}/${OPT}/${BASE_NAME}" | awk '{print $5}'
done
echo ""
echo "All compilation artifacts:"
ls -lh "${COMPILE_DIR}/"
echo ""
echo "Compilation completed successfully!"
echo "You can run programs with: ./${COMPILE_DIR}/{O0,Og,O1,O2,O3}/${BASE_NAME}"