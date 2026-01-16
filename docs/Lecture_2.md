# Lecture 2 Bits, Bites and Integers

## Representing Information as Bits

- Base 2 Number representations (十进制和二进制的转化)
- 一个 Byte 等于 8 个 Bits
    - Bit 是二进制的
    - Byte 可以由 8 个二进制数表示，因此可以表示成 2 个十六进制数。`0x`
    - 计算机内存地址通常用十六进制表示，对于 64 位的系统，虚拟内存地址编码的长度为 8 字节。
        - 理论最大的可寻址单位是 $2^64$ 个。

## Bit-level Manipulations

### Boolean Algebra

- `A & B = 1` iff `A = 1` and `B = 1`
- `A | B = 1` iff `A = 1` or `B = 1`
- `~A = 1` iff `A = 0`
- Exclusive Or (XoR): `A ^ B = 1` iff (`A = 1` or `B = 1` but not the same)

我们可以施加这四种基本运算到 Bit vectors (bit-wise operations)

### Example: DP and Binaries

在动态规划的状态压缩中，核心就是使用一个二进制数来无损压缩当前的状态。考虑表示集合 ${0,1,2,\dots,w-1}$ 的一个**子集**，状态空间的大小为 $2^w$，可以使用一个 $w$ 位的二进制数来表示这个状态。 

表示为一个 Bit Vectors 之后，布尔代数的基本运算符就对应了若干集合的基本操作：

- `&`: Intersections of sets.
- `|`: Union of sets
- `~`: Complement （补集）
- `^`: Symmetric Difference $(A \cup B) \setminus (A \cap B)$

> 在集合中，可以使用 `A & (~B)` 来表示集合的差集 $A \setminus B = A \cap \overline{B}$

### Bit Level Operations & Logic Level Operations in C

- Bit Level Operations: `&`, `|`, `~` and `^`
    - Applied to any integer data type
    - View arguments as bit vectors (applied bit-wise)
- Logic Level Operations: `&&`, `||` and `!`
    - true if the return value is not zero
    - false iff 0

### Shift Operations

- Left Shift `x << y`: Shift bit vector left y positions and throw away extra bits on the right.

- Right Shift `x >> y`

 

