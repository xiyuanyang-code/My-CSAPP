#!/bin/bash
gcc src/Lecture5/main.c src/Lecture5/math_tool.c -o src/Lecture5/pizza_shop -lm

./src/Lecture5/pizza_shop

rm src/Lecture5/pizza_shop