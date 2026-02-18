# CSAPP

> [!IMPORTANT]
> Find all the stuffs at Course Pages: [https://xiyuanyang-code.github.io/My-CSAPP/](https://xiyuanyang-code.github.io/My-CSAPP/)

## Introduction

Dive into the world of the computer systems. This repo maintains all source codes (including labs and supplementary C/C++ codes) and detailed learning markdown notes while learning CSAPP (2015, 15-­213: Introduction to Computer Systems).

## Source Code and Demonstrations

### Files

```text
.
├── Dockerfile
├── docs
│   ├── assets
│   │   ├── favicon
│   │   ├── Lecture2
│   │   ├── Lecture4
│   │   └── Lecture5
│   ├── index.html
│   ├── notes
│   │   ├── Lecture_1.md
│   │   ├── Lecture_2_3.md
│   │   ├── Lecture_4.md
│   │   ├── Lecture_5.md
│   │   └── Lecture_6.md
│   └── style.css
├── makefile
├── README.md
├── run.sh
├── scripts
│   ├── check_system.sh
│   └── run_docker_ubuntu.sh
└── src
    ├── Labs
    │   ├── attacklab
    │   ├── bomblab
    │   ├── cachelab
    │   ├── datalab
    │   ├── malloclab
    │   ├── proxylab
    │   ├── README.md
    │   └── tshlab
    ├── Lecture1
    │   ├── hello.c
    │   ├── memory_bug.c
    │   └── show_compile.sh
    ├── Lecture2
    │   ├── bit_operations.cpp
    │   ├── casting.cpp
    │   ├── endian.cpp
    │   ├── overflow.c
    │   ├── puzzles.c
    │   ├── show_bytes.c
    │   ├── signed_multiplications.c
    │   ├── string.c
    │   └── t_min.c
    ├── Lecture4
    │   ├── casting_fp.c
    │   ├── dynamic_range.py
    │   ├── floating_number.c
    │   └── rounding.py
    ├── Lecture5
    │   ├── main.c
    │   ├── math_tool.c
    │   ├── math_tool.h
    │   ├── multiply.c
    │   ├── multiply.s
    │   ├── pointer.c
    │   ├── pointer.s
    │   ├── swap.c
    │   └── swap.s
    └── scripts
        ├── compile_example.sh
        ├── get_assemble.sh
        └── show_temp_file.sh
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

### Gcc & GNU Docker (For `MacOS` Only)

Given binaries of several labs (e.g. datalab) are compiled and executed on x86 architecture, therefore, it cannot be executed on M-series Macs because the binaries are compiled for the x86 architecture. Thus, this repo gives you a prepared environment that runs successfully on `Docker`.

```bash
# build docker images
docker build --platform linux/amd64 -t csapp .
```

- After building, running `docker images`, then there should be:

```text
REPOSITORY    TAG       IMAGE ID       CREATED              SIZE
csapp         latest    6fb63ad3031a   About a minute ago   2.25GB
```

- Running Commands:

```bash
bash scripts/run_docker_ubuntu.sh
```

- Checking Environments:

```bash
bash scripts/check_system.sh
```

```text
x86_64
gcc (GCC) 15.2.0
GNU gdb (Debian 16.3-1) 16.3
```

## Notes and Materials

- `20260109`: Finish Lecture 1, the basic introduction of the work.
- `20260116`: Finish Lecture 2, about bit level operations and integer manipulations.
- `20260116`: Start wracking on Lab1 Data Labs.
- `20260213`: Finish Lecture 3, about additions and multiplications of integers.
- `20260214`: Finish Lecture 4, about floating points manipulations and calculations.
- `20260217`: Finish Lecture 5, machine level programming I: Basics.
- `20260218`: Finish Lab1: DataLab & Docker Environments


