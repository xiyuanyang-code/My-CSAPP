# Machine Level Programming III: Procedures

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.css">

<script defer src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.js"></script>

<script defer src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/contrib/auto-render.min.js" onload="renderMathInElement(document.body, {delimiters: [
    {left: '$$', right: '$$', display: true},
    {left: '\\[', right: '\\]', display: true},
    {left: '$', right: '$', display: false},
    {left: '\\(', right: '\\)', display: false}
]});"></script>

## Mechanisms in Procedures

### ABI & API

**ABI** (Application Binary Interface) 是计算机体系结构中 **运行环境（Runtime）** 与 **目标代码（Object Code）** 之间的一套完全确定的低级接口协议。它在**二进制层面**强制规范了机器码执行时的所有细节:
- 指令集架构（ISA）
- 数据类型的位宽与内存对齐方式
- 寄存器分配策略与函数调用规约（Calling Convention）
- 系统调用的陷阱机制（Trap Mechanism）。

其核心意义在于确保遵循同一规范的独立编译单元（如可执行文件与动态链接库）无需重新编译，即可在符合该规范的硬件与操作系统上实现**二进制级别的互操作性（Interoperability）**。

### Mechanisms

从程序运行的角度来说，往往需要关注如下的流程:

- Passing Control:
    - 发生函数调用时控制权的转移
    - 函数调用结束时控制权的交回
- Passing Data
    - 参数传入
    - 返回值
- Memory Management
    - 内存的分配机制 (Allocate & Deallocate)

Mechanisms all implemented with machine instructions.

## Stack Structures

## Calling Conventions

## Illustration of Recursions

