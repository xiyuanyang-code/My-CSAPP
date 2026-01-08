# CSAPP

## Introduction

Dive in, into the world of the computer systems.

## Usage

### Using Makefile

Compile and run C/C++ files:

```bash
make f=file.c          # Compile and run C file
make f=file.cpp        # Compile and run C++ file
```

Example:
```bash
make f=Lecture1/memory_bug.c
```

### Using Shell Script

Alternative method:

```bash
./run.sh file.c        # Compile and run C file
./run.sh file.cpp      # Compile and run C++ file
```

Build artifacts are stored in the `build/` directory.