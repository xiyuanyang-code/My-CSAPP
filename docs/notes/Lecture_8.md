# Machine Level Programming IV: Data

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.css">

<script defer src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.js"></script>

<script defer src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/contrib/auto-render.min.js" onload="renderMathInElement(document.body, {delimiters: [
    {left: '$$', right: '$$', display: true},
    {left: '\\[', right: '\\]', display: true},
    {left: '$', right: '$', display: false},
    {left: '\\(', right: '\\)', display: false}
]});"></script>

## Introduction

在之前的课程中，我们详细介绍了 C 语言中一些基本类型的表示：

- 整数（不同位数的整数，有符号和无符号）
- 浮点数
- 布尔值（一种特殊的整数）
- Char & Strings
- 指针类型

高级编程语言（包括 C）都需要更加复杂的数据结构来进行表示和建模，例如列表、结构体等等。如此之类复杂的、可动态变化的**复合数据类型**在程序运行和汇编语言中的表示更加的复杂。

- Arrays
- Structs
- Floating Points