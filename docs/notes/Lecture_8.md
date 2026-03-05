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

## Array

`T A[L]`: 
- T is thr array of data type
- the length of the array: L

在栈上**连续分配** `L * sizeof(T)` bytes。

> **数组就是指针！**，数组变量在 C 代码中可以被用作一个 `T*` 类型的指针。

```c
#include <stdio.h>
#define ZLEN 6
typedef int zip_dig[ZLEN];

void show_pointer() {
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9};
  printf("%p\n", arr);
  printf("%p\n", arr + 1);

  char arr_2[10] = {'1', '2', '3'};
  printf("%p\n", arr_2);
  printf("%p\n", arr_2 + 1);

  //   or another methods
  zip_dig cmu = {1, 5, 2, 1, 3};
  printf("%p\n", cmu);
  printf("%p\n", cmu + 1);

  //   this will cause damage
  //   arr += 1;
}

int main() {
  show_pointer();
  return 0;
}
```

```text
0x16d8d1dd0
0x16d8d1dd4
0x16d8d1dc0
0x16d8d1dc1
0x16d8d1da0
0x16d8d1da4
```

可以看到 arr_2 在栈内存中的地址**低于** arr，但是在指针变量内部，顺序又是从**高位到低位的**，因此可以发现**数组**在程序运行时的处理是比较特殊的。回忆一下在第五讲讲到的 Memory Addressing Modes:

`D(Rb, Ri, S)`: `Mem[Reg[Rb] + S*Reg[Ri] + D]`

- `S`: 1,2,4,8 (扩展寄存器支持特定的后缀寻址方式)
- Rb: Base register
- Ri: Index register

![Addressing Modes](../assets/Lecture5/address_modes.png)

很显然，在数组中内存的访问非常方便使用这种模式进行：

```c
#define ZLEN 6
typedef int zip_dig[ZLEN];

int get_digit(zip_dig z, int digit) { return z[digit]; }
```

```assembly
	.file	"memory_addressing_modes.c"
	.text
	.globl	get_digit
	.type	get_digit, @function
get_digit:
.LFB0:
	.cfi_startproc
	movslq	%esi, %rsi
	movl	(%rdi,%rsi,4), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	get_digit, .-get_digit
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
```

`movl	(%rdi,%rsi,4), %eax` 这一条指令代表从 %rdi（第一个输入参数，指针变量）开始作为 base register，然后以 4 字节为基本单位索引向后移动 `%rsi` 个单元，并取址读取值，存储到寄存器 `%eax` 中（函数的返回值）

再看一个更难的例子：

```c
void zincr(zip_dig z) {
  size_t i;
  for (i = 0; i < ZLEN; i++) {
    z[i]++;
  }
}
```

```assembly
zincr:
.LFB1:
	.cfi_startproc
	movl	$0, %eax
	jmp	.L3
	.p2align 5
.L4:
	leaq	(%rdi,%rax,4), %rcx
	movl	(%rcx), %esi
	leal	1(%rsi), %edx
	movl	%edx, (%rcx)
	addq	$1, %rax
.L3:
	cmpq	$5, %rax
	jbe	.L4
	ret
	.cfi_endproc
```

- `%rax` 寄存器始终进行 for 循环下标 i 的读取和更新
- `leaq	(%rdi,%rax,4), %rcx`: 读取对应数组下标的**地址**（注意 mov 和 lea 的指令功能不同，leaq 不会从内存中读取具体的值）
- `movl    (%rcx), %esi`: 从内存地址 %rcx 取出值，存入 %esi (即 val = arr[i])
- `leal    1(%rsi), %edx`: 利用 leal 计算 %rsi + 1，结果存入 %edx
- `movl    %edx, (%rcx)`: 将加 1 后的值写回内存地址 %rcx (即 arr[i] = val + 1)
    - 这里的自增操作貌似显的有点多余，实则也是后置++的特性，需要返回自增之前的值，因此需要使用单独一个变量进行存储。

### Nested Arrays

- `T A[R][C]`: 2D data array of data type `T`
- R rows, C columns
- Type `T` element requires `K` bytes.

- Total size: R * C * K

在内存中的存储结构和正常的一样。

$$
A+i*(C*K)+j*K = A+(i*C+j)*K
$$

```c
#include <stdio.h>
#define PCOUNT 4
#define ZLEN 6
typedef int zip_dig[ZLEN];

zip_dig pgh[PCOUNT] = {
    {1, 5, 2, 0, 6}, {1, 5, 2, 1, 3}, {1, 5, 2, 1, 7}, {1, 5, 2, 2, 1}};

int *get_pgh_zip(int index) { return pgh[index]; }

int get_pgh_digit(int index, int dig) { return pgh[index][dig]; }

```

```assembly
get_pgh_zip:
.LFB11:
	.cfi_startproc
	movslq	%edi, %rdi
	leaq	(%rdi,%rdi,2), %rax
	leaq	pgh(,%rax,8), %rax
	ret
	.cfi_endproc
.LFE11:
	.size	get_pgh_zip, .-get_pgh_zip
	.globl	get_pgh_digit
	.type	get_pgh_digit, @function
get_pgh_digit:
.LFB12:
	.cfi_startproc
	movslq	%esi, %rsi
	movslq	%edi, %rdi
	leaq	(%rdi,%rdi,2), %rax
	leaq	(%rsi,%rax,2), %rax
	movl	pgh(,%rax,4), %eax
	ret
	.cfi_endproc
.LFE12:
	.size	get_pgh_digit, .-get_pgh_digit
	.globl	pgh
	.data
	.align 32
	.type	pgh, @object
	.size	pgh, 96
```

- In `get_pgh_zip` function:
    - `leaq	(%rdi,%rdi,2), %rax`: rax = 3 * rdi
    - `leaq	pgh(,%rax,8), %rax`: $\text{rax} = \text{pgh} + (\text{rax} \times 8)$
    - 两行计算整体进行：`rax = pgh + 24 * rdi`, 24 = 3*8= 4*6!
        - 不得不感叹，聪明的编译器
- In `get_pgh_digit` function:
    - `leaq	(%rdi,%rdi,2), %rax`: `rax = 3*rdi`
    - `leaq	(%rsi,%rax,2), %rax`: `rax = rsi + rax*2`
    - 合起来：`rax = rsi + 6* rdi`
        - `rdi` 对应第一个参数 index
        - `rsi` 对应第二个参数 dig
    - `movl	pgh(,%rax,4), %eax`: eax 的值是 `pgh + 4*(rsi + 6*rdi)` 的地址上的数取值得到的结果。

### Multi-Level Array

在生成一个 Nested Array 的时候，**整个数组的元素**都存储在**栈上**的一段连续空间，可以快速通过索引计算得到，在上文的汇编中也展示了使用 leap 等汇编指令进行内存区域的快速访问。

但是如下的声明方式存在差异：

```c
#include <stddef.h>
#include <stdio.h>
#define PCOUNT 4
#define ZLEN 6
#define UCOUNT 3
typedef int zip_dig[ZLEN];

zip_dig pgh[PCOUNT] = {
    {1, 5, 2, 0, 6}, {1, 5, 2, 1, 3}, {1, 5, 2, 1, 7}, {1, 5, 2, 2, 1}};

zip_dig cmu = {1, 5, 2, 1, 3};
zip_dig mit = {0, 2, 1, 3, 9};
zip_dig ucb = {9, 4, 5, 2, 0};

int *univ[UCOUNT] = {mit, cmu, ucb};
// univ 也是一个二维数组（二维指针），在这里表示成一个一维指针的数组

int *get_pgh_zip(int index) { return pgh[index]; }

int get_pgh_digit(int index, int dig) { return pgh[index][dig]; }

int get_univ_digit(size_t index, size_t digit) { return univ[index][digit]; }
```

`univ` 是一个一维数组的指针，因此三个指针变量存储在连续的内存中，但是**三个指针指向的内容**存储在**不同的内存区域**中。

```assembly
get_univ_digit:
.LFB13:
	.cfi_startproc
	movq	univ(,%rdi,8), %rax
	movl	(%rax,%rsi,4), %eax
	ret
	.cfi_endproc
```

- `movq	univ(,%rdi,8), %rax` 将对应的一维数组中**元素**读取出来，注意这里是 `movq` 会从内存中取值。
- 取出来的值仍然是一个地址！（因为这个数组的元素是一个 int 类型的指针），接下来再读取 rsi 中的第二个函数输入参数，读取到最终的 digit。

> 对于 Multi-Level Array，需要**多次的解引用操作**。

### VLA

在 C99 中，引入了变长数组 Variable Length Array，允许**数组的长度在运行时确定而不是在编译时确定**。

```c
#include <stddef.h>

int vec_ele(size_t n, int a[n][n], size_t i, size_t j) { return a[i][j]; }
```

```assembly
vec_ele:
.LFB0:
	.cfi_startproc
	imulq	%rdx, %rdi
	leaq	(%rsi,%rdi,4), %rax
	movl	(%rax,%rcx,4), %eax
	ret
	.cfi_endproc
```

- `rax = rsi + 4* (rdi * rdx)`
    - rdx is `i`, and rdi is `n`
    - rax 读取了第一个索引对应的地址
- `movl	(%rax,%rcx,4), %eax`: 加上了第四个参数 rcx 并读取，最终读取到对应的内存位置并取得对应的值，存储在 rax 寄存器中返回。

## Structs

### Allocations

### Access

### Alignment


