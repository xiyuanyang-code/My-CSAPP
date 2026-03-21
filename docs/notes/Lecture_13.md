# Linking

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.css">

<script defer src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.js"></script>

<script defer src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/contrib/auto-render.min.js" onload="renderMathInElement(document.body, {delimiters: [
    {left: '$$', right: '$$', display: true},
    {left: '\\[', right: '\\]', display: true},
    {left: '$', right: '$', display: false},
    {left: '\\(', right: '\\)', display: false}
]});"></script>

在之前的课程中，我们学习了：

- 基本位运算和二进制运算
- C 语言中的基本变量类型: (unsigned/signed) integers, floating numbers, arrays, structs, pointers, strings...
- Machine Level Programming: 如何将人类**可读的运行逻辑**从硬件视角转化为汇编指令
    - 从汇编出发、深入理解程序运行的更深入逻辑
- 程序性能优化：如何写出更加编译友好的代码
- 存储：存储结构 & 缓存机制

然而，现代软件工程的功能日益复杂，在硬件之上，软件之间的交互也是理解程序运行细节的一个非常重要的方向和模块。

```c
#include <stdio.h>
int sum(int *a, int n);

int array[2] = {1, 2};

int main(){
    int val = sum(array, 2);
    printf("Current value: %d\n", val);
    return 0;
}

// run with: gcc -Og -o src/Lecture13/example_program/prog_example src/Lecture13/example_program/main.c src/Lecture13/example_program/sum.c
```

```c
int sum(int *a, int n){
    int i, s = 0;
    for (i = 0; i < n; i++){
        s += a[i];
    }
    return s;
}
```

编译（Compilation）是针对每个源文件单独进行的，而链接（Linking）是在所有文件编译完成后，将它们合并在一起的过程。