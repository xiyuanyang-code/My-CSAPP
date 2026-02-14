# CSAPP

## Introduction

Dive into the world of the computer systems. This repo maintains all source codes (including labs and supplementary C/C++ codes) and detailed learning markdown notes while learning CSAPP (2015, 15-­213: Introduction to Computer Systems).

## Source Code and Demonstrations

### Files

```text
.
├── docs
│   ├── assets
│   │   ├── favicon
│   │   └── Lecture2
│   ├── index.html
│   ├── Lecture_1.md
│   ├── Lecture_2_3.md
│   └── style.css
├── makefile
├── README.md
├── run.sh
└── src
    ├── Labs
    │   └── datalab
    ├── Lecture1
    │   ├── hello.c
    │   ├── memory_bug.c
    │   └── show_compile.sh
    └── Lecture2
        ├── bit_operations.cpp
        ├── casting.cpp
        ├── endian.cpp
        ├── overflow.c
        ├── puzzles.c
        ├── show_bytes.c
        ├── signed_multiplications.c
        ├── string.c
        └── t_min.c
```

### Usage

Compile and run C/C++ files, or just simply using the wrapped shell script.

```bash
make f=file.c          # Compile and run C file
make f=file.cpp        # Compile and run C++ file
```

```bash
./run.sh file.c        # Compile and run C file
./run.sh file.cpp      # Compile and run C++ file
```

For example:

```bash
bash run.sh src/Lecture2/puzzles.c
# It will compile the target file, showing output in terminal and move all build artifacts to `build` directory.
```

Build artifacts are stored in the `build/` directory.

## Notes and Materials

- `20260109`: Finish Lecture 1, the basic introduction of the work.
- `20260116`: Finish Lecture 2, about bit level operations and integer manipulations.
- `20260116`: Start wracking on Lab1 Data Labs.
- `20260213`: Finish Lecture 3, about additions and multiplications of integers.


