# Lecture 2-3 Bits, Bites and Integers

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.css">

<script defer src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/katex.min.js"></script>

<script defer src="https://cdn.jsdelivr.net/npm/katex@0.16.9/dist/contrib/auto-render.min.js" onload="renderMathInElement(document.body);"></script>

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

- Left Shift `x << y`: Shift bit vector left y positions and throw away extra bits on the right and fill with 0 on the left.

- Right Shift `x >> y`: Shift bit vector right y positions and throw away extra bits on the left and fill with 0 on the right.

> Attention! Doing shift operations for negative numbers is UB.

```c
void show_shift_operations() {
  unsigned char a = 0x41;

  printf("--- Shift Operations (unsigned char) ---\n");
  printf("Original: 0x%02X (Binary: ", a);
  print_binary(a);
  printf(")\n");

  unsigned char left_shift_result = (unsigned char)(a << 3);
  printf("Left Shift 3 positions:  0x%02X (Binary: ", left_shift_result);
  print_binary(left_shift_result);
  printf(")\n");

  unsigned char right_shift_result = (unsigned char)(a >> 2);
  printf("Right Shift 2 positions: 0x%02X (Binary: ", right_shift_result);
  print_binary(right_shift_result);
  printf(")\n");
}

void show_signed_shift_dangers() {
  // ! Undefined behaviors
  signed char a = -0x41;  // -65 in decimal
  unsigned char b = 0x41; // 65 in decimal for comparison

  printf(
      "\n--- Signed Shift Dangers (Arithmetic vs Logical Right Shift) ---\n");

  printf("\n[SIGNED CHAR - Arithmetic Right Shift]\n");
  printf("Original: %d (0x%02X) (Binary: ", a, (unsigned char)a);
  print_binary(a);
  printf(")\n");

  signed char right_shift_2 = (signed char)(a >> 2);
  printf("Right Shift 2 positions: %d (0x%02X) (Binary: ", right_shift_2,
         (unsigned char)right_shift_2);
  print_binary(right_shift_2);
  printf(")\n");
  signed char right_shift_4 = (signed char)(a >> 4);
  printf("Right Shift 4 positions: %d (0x%02X) (Binary: ", right_shift_4,
         (unsigned char)right_shift_4);
  print_binary(right_shift_4);
  printf(")\n");

  printf("\n[UNSIGNED CHAR - Logical Right Shift]\n");
  printf("Original: %d (0x%02X) (Binary: ", b, b);
  print_binary(b);
  printf(")\n");

  unsigned char right_shift_2_u = b >> 2;
  printf("Right Shift 2 positions: %d (0x%02X) (Binary: ", right_shift_2_u,
         right_shift_2_u);
  print_binary(right_shift_2_u);
  printf(")\n");
}
```

```text
--- Signed Shift Dangers (Arithmetic vs Logical Right Shift) ---

[SIGNED CHAR - Arithmetic Right Shift]
Original: -65 (0xBF) (Binary: 10111111)
Right Shift 2 positions: -17 (0xEF) (Binary: 11101111)
Right Shift 4 positions: -5 (0xFB) (Binary: 11111011)

[UNSIGNED CHAR - Logical Right Shift]
Original: 65 (0x41) (Binary: 01000001)
Right Shift 2 positions: 16 (0x10) (Binary: 00010000)
```

> [!NOTE]
> `unsigned_char` 类型的字段在 C/Cpp 中被严格定义为 1 个字节即 8 个比特位，正好可以对应一个**两位的二进制数**。从计算机的视角，一个 char 字符也可以看成是一个两位的二进制数！并且使用 `unsigned` 防止负号影响对应的行为。

```text
--- Shift Operations (unsigned char) ---
Original: 0x41 (Binary: 01000001)
Left Shift 8 positions:  0x00 (Binary: 00000000)
Right Shift 8 positions: 0x00 (Binary: 00000000)
--- Shift Operations (unsigned char) ---
Original: 0xFFFFFFBF (Binary: 10111111)
Left Shift 8 positions:  0x00 (Binary: 00000000)
Right Shift 8 positions: 0xFF (Binary: 11111111)
```
 
## Integers

### Encoding Integers

我们首先需要在计算机中表示（十进制）整数。一个 int 类型的变量是 4 字节。

- 对于无符号整数，32 位字节全部用来存储整数的二进制数据，即一个 $w = 32$ 的二进制字符串。

$$
\text{B2U}(X) = \sum_{i=0}^{w-1} x_i 2^i
$$

- 二进制转补码成为有符号整数 (Binary to Two's Complement)，因为需要预留一个比特给 0/1 的位置，因此需要额外加上符号位。

$$
\text{B2T} = - x_{w-1} 2^{w-1} + \sum_{i=0}^{w-2} x_i 2^i
$$

> [!NOTE]
> 补码的计算方式（正数不变、负数取反加一）对应的就是这个核心的计算模式。在 $w$ 位的二进制中，最高位（MSB）的权重在无符号（$B2U$）时是 $2^{w-1}$，而在补码（$B2T$）时是 $-2^{w-1}$。这两者之间的差值恰好是：$$2^{w-1} - (-2^{w-1}) = 2 \times 2^{w-1} = 2^w$$这意味着，补码本质上是在模 $2^w$ 的系统下进行的运算。这也对应这整数的溢出现象。
> 假设我们有一个正数 $x$（源码为 $0 \dots$），我们要得到它的相反数 $-x$ 的补码表示。将 $x$ 的每一位取反，数学上等同于用全 1 的二进制数（即 $2^w - 1$）减去 $x$。
$$\text{取反结果} = (2^w - 1) - x$$
$$\text{补码} = ((2^w - 1) - x) + 1 = 2^w - x$$
对应 $B2T$ 公式：当你计算 $2^w - x$ 时，在 $w$ 位长的容器里，最高位的溢出会被丢弃（对应数学上的取模运算），留下的位模式正好满足 $B2T$ 公式中 $-2^{w-1}$ 的权重分配，使得最终结果的数学意义等同于 $-x$。


无论是有符号整数的补码表示，还是无符号整数，其表示的整数的区间长度都是固定不变的，都是 $2^w$，这也说明了整数在计算机中就像一个时钟一样，二进制位的长度使其走完一圈的模长为 $2^w$。在这个基础上，只要保证模长相同的条件下，我们可以保证**补码合成的整数**和无符号整数之前存在**一一对应的函数关系**。这为后续语言的进制转换提供了理论基础（保证这种转换存在唯一性）

使用补码的性质可以在 bit-level 上完成很多基本的数学操作，例如 $x \to -x$：可以通过**按位取反并加一**的格式进行运算：

这涉及到补码设计的数学本质。在 $w$ 位的二进制系统中，一个数 $x$ 和它的按位取反结果 $\sim x$ 相加，每一位都会变成 $1$：$$x + \sim x = 111...111_2 = 2^w - 1$$根据模运算定义，$2^w$ 在该位宽下等同于 $0$。所以：$$x + (\sim x + 1) = 2^w \equiv 0 \pmod{2^w}$$既然 $x$ 加上 $(\sim x + 1)$ 等于 $0$，那么 $(\sim x + 1)$ 理所当然就是 $x$ 的加法逆元（即相反数）。

```c
#include "limits.h"
#include "stdio.h"

int get_negative_value(int x) { return (~x + 1); }

int main() {
  int a = 10;
  printf("Normal cases for int numbers:\n");
  printf("The negative number of %d is %d\n", a, get_negative_value(a));

  int b = INT_MIN;
  printf("Special cases for TMIN\n");
  printf("The negative number of %d is %d\n", b, get_negative_value(b));
  return 0;
}
```

```text
Normal cases for int numbers:
The negative number of 10 is -10
Special cases for TMIN
The negative number of -2147483648 is -2147483648
```

![Signed and Unsigned](assets/Lecture2/signed_and_unsigned.png)

```c
void show_integers(short number) {
  printf("\n--- Integer Representations (short: 16 bits) ---\n");

  printf("\n[Input Number]\n");
  printf("Value: %d (0x%04hX) (Binary: ", number, number);
  SHOW_BINARY(number);
  printf(")\n");

  printf("\n[Special Values]\n");

  unsigned short max_unsigned_short = 0xFFFF;
  printf("Max unsigned short: %6hu (0x%04hX) (Binary: ", max_unsigned_short, max_unsigned_short);
  SHOW_BINARY(max_unsigned_short);
  printf(")\n");

  short max_short = 0x7FFF;
  printf("Max signed short:   %6hd (0x%04hX) (Binary: ", max_short, max_short);
  SHOW_BINARY(max_short);
  printf(")\n");

  short min_short = 0x8000;
  printf("Min signed short:   %6hd (0x%04hX) (Binary: ", min_short, min_short);
  SHOW_BINARY(min_short);
  printf(")\n");

  short minus_1 = -1;
  printf("Minus one for short (-1):     %6hd (0x%04hX) (Binary: ", minus_1, (unsigned short)minus_1);
  SHOW_BINARY(minus_1);
  printf(")\n");

  short zero = 0;
  printf("Zero (0):           %6hd (0x%04hX) (Binary: ", zero, zero);
  SHOW_BINARY(zero);
  printf(")\n");
}
```

```text
--- Integer Representations (short: 16 bits) ---

[Input Number]
Value: 32 (0x0020) (Binary: 0000000000100000)

[Special Values]
Max unsigned short:  65535 (0xFFFF) (Binary: 1111111111111111)
Max signed short:    32767 (0x7FFF) (Binary: 0111111111111111)
Min signed short:   -32768 (0x8000) (Binary: 1000000000000000)
Minus one (-1):         -1 (0xFFFF) (Binary: 1111111111111111)
Zero (0):                0 (0x0000) (Binary: 0000000000000000)
```

可以看到，同样都是 1111111111111111 的二进制表示（16 个 bits），对于不同的类型声明（比如 unsigned short 和 short），其解析的方式和最终的结果大相径庭。

### Casting Surprises

If there is a mix of unsigned and signed in single expression, **signed values with implicitly cast to unsigned**, this includes comparison operations: `<`, `>`, etc.

While doing casting, the bit pattern remains **maintained**, but reinterpreted.（系统的类型转换，无论是强制的还是非强制的，都不会改变系统内存中的 0/1 状态）

#### `abs(INT_MIN)`

由于有符号数使用补码表示，负数范围比正数范围多一个。对于 64 位的系统，int 的最大整数是2147483647，最小整数是 -2147483648。这意味着 $-2147483648$ 没有对应的正数可以表示在 `int` 类型中。因此，总可以找到一个最小的负值，使其成为正数的时候会发生溢出现象。

```c
void abs_corner_case(int number = 0) {
  int int_max = INT_MAX;
  int int_min = INT_MIN;
  printf("The maximum value of int is %d\n", int_max);
  printf("The minimum value of int is %d\n", int_min);
  printf("The abs of given number %d is %d\n", number, std::abs(number));
  // The abs of given number -2147483648 is -2147483648
  printf("%u\n", ((UINT_MAX << 1) + 1));
  assert((UINT_MAX << 1) + 1 == UINT_MAX);
}
```

#### Dangerous unsigned integers

```c
void dangerous_operations() {
  unsigned i = 5;
  for (; i >= 0; i--) {
    printf("Entering the Loops");
  }
}
```

### Expanding and Truncating

Given the $w$-bit signed integer $x$, we need to convert is into $w + k$-bit integer with the same value. (Like casting from `int` to `long long`)

The rule is making copies bit-wise, and fill with $k$ copies of sign bit $x_{w-1}$.

$$
X' = x_{w-1}, \dots,x_{w-1}, x_{w-1}, x_{w-2}, \dots, x_0
$$

证明的关键在于**最高位（符号位）具有负权重**。

对于一个 $w$ 位的补码 $[x_{w-1}, x_{w-2}, \dots, x_0]$，其对应的真值 $B_w(x)$ 定义为：

$$B_w(x) = -x_{w-1} \cdot 2^{w-1} + \sum_{i=0}^{w-2} x_i \cdot 2^i$$

设新序列为 $x'$，其位宽为 $w+1$。根据定义：

$$B_{w+1}(x') = -x_{w-1} \cdot 2^w + x_{w-1} \cdot 2^{w-1} + \sum_{i=0}^{w-2} x_i \cdot 2^i$$

我们提取前两项中共同的 $x_{w-1}$：

$$B_{w+1}(x') = x_{w-1}(-2^w + 2^{w-1}) + \sum_{i=0}^{w-2} x_i \cdot 2^i = -x_{w-1} \cdot 2^{w-1} + \sum_{i=0}^{w-2} x_i = B_w(x)$$

结论：$B_{w+1}(x') = B_w(x)$。证明完毕。

既然增加 1 位能保持数值不变，那么通过数学归纳法，重复上述过程 $k$ 次，增加 $k$ 个符号位，其数值依然会保持恒定。

从几何直观上理解，这其实是一个**幂级数求和**的过程：当你添加 $k$ 个符号位时，你实际上是在负权重位移动后，用一串正权重位去“填补”那个差值。对于符号位 $x_{w-1} = 1$（负数）的情况，增加位的贡献是：$$-2^{w+k-1} + 2^{w+k-2} + 2^{w+k-3} + \dots + 2^{w-1}$$根据等比级数求和公式，后面那一串正权重的和等于 $2^{w+k-1} - 2^{w-1}$。两者相加，结果正好是 $-2^{w-1}$，即原始符号位的权重。

```c
void sign_extensions() {
  int a = 5e8;
  SHOW_BINARY(a);
  printf("\n");
  printf("The size of b is %lu\n", sizeof(a));

  long long b = (long long)a;
  SHOW_BINARY(b);
  printf("\n");
  printf("The size of b is %lu\n", sizeof(b));

  int c = -5e8;
  SHOW_BINARY(c);
  printf("\n");
  printf("The size of c is %lu\n", sizeof(c));

  long long d = (long long)c;
  SHOW_BINARY(d);
  printf("\n");
  printf("The size of d is %lu\n", sizeof(d));
}
```

```text
00011101110011010110010100000000
The size of b is 4
0000000000000000000000000000000000011101110011010110010100000000
The size of b is 8
11100010001100101001101100000000
The size of c is 4
1111111111111111111111111111111111100010001100101001101100000000
The size of d is 8
```

For the truncating process, like casting `unsigned` into `unsigned short`, bits are truncated rudely.


### Addition, Negation, Multiplication, Shifting

#### Unsigned Addition

对于两个具备 $w$ 位的无符号整数进行加和操作，理论上需要 $w+1$ 位的无符号整数才能准确的进行编码。很可惜的是，为了保证编码的对齐和一致性，我们将会丢弃最高位上的数位，使用一个 $w$ 位的无符号整数来进行编码。产生的数位丢弃现象就是**正溢出**。

### Two's Complement Addition

$$
(a + b)\ \text{mod} \ m = ((a \ \text{mod} \ m) + (b \ \text{mod} \ m)) \text{mod} \ m
$$

使用补码来表示有符号整数，但是 `TAdd` 和 `UAdd` 在比特位的水平上执行的操作是完全相同的。（加法竖式的操作）

在 TAdd 中，同样会发生溢出现象。不过一般来说，发生溢出现象的符号位和预期的符号位是相反的：

- 例如，两个很大的正数相加，数位进位占据符号位导致符号位从 0 变成 1，最终导致输出的是一个负数
- 例如，两个很小（绝对值很大）的负数相加，本身符号位的进位导致符号位从 1 变成 0，最终输出是一个正数（绝对值很小）。

> 溢出的本质是数据超过了容器的边界

对于 $w$ 位的有符号整数而言，可以表示的范围是：$[-2^{w-1}, 2^{w-1}-1]$，因此两者加和可能的范围是：

$$
\text{TAdd} \in [-2^{w}, 2^{w}-2]
$$

因此，如果加和结果在 $[-2^{w}, -2^{w-1})$, $(2^{w-1}-1, 2^{w}-2]$ 这个区间中的会发生溢出行为。

```c
#include <stdio.h>
#include <limits.h>

void print_short_binary(short num) {
    printf("Decimal: %6d | Hex: 0x%04X | Binary: ", num, (unsigned short)num);

    for (int i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_ushort_binary(unsigned short num) {
    printf("Decimal: %6u | Hex: 0x%04X | Binary: ", num, num);

    for (int i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void show_uadd_overflow() {
    printf("\n========== Unsigned Addition Overflow ==========\n");
    printf("Using unsigned short (16 bits), Max value: %u\n\n", USHRT_MAX);

    unsigned short a = 0xFFFF;
    unsigned short b = 0x0001;
    unsigned short result = a + b;

    printf("Adding: %u + %u\n", a, b);
    printf("\nOperand a:\n");
    print_ushort_binary(a);
    printf("\nOperand b:\n");
    print_ushort_binary(b);
    printf("\nResult (wrapped around to 0):\n");
    print_ushort_binary(result);

    printf("\nExplanation: 0xFFFF + 0x0001 = 0x10000, but only lower 16 bits are kept\n");
}

void show_tadd_overflow() {
    printf("\n========== Signed Addition Overflow ==========\n");
    printf("Using short (16 bits), Range: [%d, %d]\n\n", SHRT_MIN, SHRT_MAX);

    short pos1 = 0x7FFF;
    short pos2 = 0x7FFE;
    short result1 = pos1 + pos2;

    printf("Case 1: Positive + Positive (Positive Overflow)\n");
    printf("Adding: %d + %d\n", pos1, pos2);
    printf("\nOperand a:\n");
    print_short_binary(pos1);
    printf("\nOperand b:\n");
    print_short_binary(pos2);
    printf("\nResult (overflow to negative):\n");
    print_short_binary(result1);
    printf("\n");

    short neg1 = 0x8000;
    short neg2 = 0x800E;
    short result2 = neg1 + neg2;

    printf("Case 2: Negative + Negative (Negative Overflow)\n");
    printf("Adding: %d + %d\n", neg1, neg2);
    printf("\nOperand a:\n");
    print_short_binary(neg1);
    printf("\nOperand b:\n");
    print_short_binary(neg2);
    printf("\nResult (overflow to positive):\n");
    print_short_binary(result2);
    printf("\n");

    short neg3 = 0x8000;
    short pos3 = 0x7FFF;
    short result3 = neg3 + pos3;

    printf("Case 3: Negative + Positive (Normal)\n");
    printf("Adding: %d + %d\n", neg3, pos3);
    printf("\nOperand a:\n");
    print_short_binary(neg3);
    printf("\nOperand b:\n");
    print_short_binary(pos3);
    printf("\nResult (no overflow):\n");
    print_short_binary(result3);
    printf("\n");
}

int main() {
    show_uadd_overflow();
    show_tadd_overflow();
    return 0;
}
```

```text
========== Unsigned Addition Overflow ==========
Using unsigned short (16 bits), Max value: 65535

Adding: 65535 + 1

Operand a:
Decimal:  65535 | Hex: 0xFFFF | Binary: 1111 1111 1111 1111

Operand b:
Decimal:      1 | Hex: 0x0001 | Binary: 0000 0000 0000 0001

Result (wrapped around to 0):
Decimal:      0 | Hex: 0x0000 | Binary: 0000 0000 0000 0000

Explanation: 0xFFFF + 0x0001 = 0x10000, but only lower 16 bits are kept

========== Signed Addition Overflow ==========
Using short (16 bits), Range: [-32768, 32767]

Case 1: Positive + Positive (Positive Overflow)
Adding: 32767 + 32766

Operand a:
Decimal:  32767 | Hex: 0x7FFF | Binary: 0111 1111 1111 1111

Operand b:
Decimal:  32766 | Hex: 0x7FFE | Binary: 0111 1111 1111 1110

Result (overflow to negative):
Decimal:     -3 | Hex: 0xFFFD | Binary: 1111 1111 1111 1101

Case 2: Negative + Negative (Negative Overflow)
Adding: -32768 + -32754

Operand a:
Decimal: -32768 | Hex: 0x8000 | Binary: 1000 0000 0000 0000

Operand b:
Decimal: -32754 | Hex: 0x800E | Binary: 1000 0000 0000 1110

Result (overflow to positive):
Decimal:     14 | Hex: 0x000E | Binary: 0000 0000 0000 1110
```

![Overflow Visualizations](assets/Lecture2/overflow.png)

### Multiplications

Goal: Compute product of w-bit numbers x and y.
For the usage of memory, we will truncate that into $w$ bits. (Overflow Again!)

#### Unsigned Multiplications in C

对于两个 $w$ 位的无符号整数，最大相乘得到的数是 $(2^{w}-1)^2$ 需要使用 $2w$ 的数位进行编码，我们依然采用截断的策略，即只保留最低位的 $w$ 位。

具体的运算策略，二进制数和十进制数保持一致。

```c
void print_ushort_binary(unsigned short num) {
    printf("Decimal: %6u | Hex: 0x%04X | Binary: ", num, num);

    for (int i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_uint_binary(unsigned int num) {
    printf("Decimal: %10u | Hex: 0x%08X | Binary: ", num, num);

    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void show_umul_overflow() {
    printf("\n========== Unsigned Multiplication Overflow ==========\n");
    printf("Using unsigned short (16 bits), Max value: %u\n\n", USHRT_MAX);
    unsigned short a2 = 544;
    unsigned short b2 = 566;
    unsigned short result2 = a2 * b2;
    unsigned int full_result2 = (unsigned int)a2 * b2;

    printf("Multiplying: %u * %u = %u (truncated from %u)\n", a2, b2, result2, full_result2);
    printf("\nOperand a:\n");
    print_ushort_binary(a2);
    printf("\nOperand b:\n");
    print_ushort_binary(b2);
    printf("\nFull 32-bit product:\n");
    print_uint_binary(full_result2);
    printf("\n");
    printf("Truncated to 16 bits (only lower half):\n");
    print_ushort_binary(result2);
    printf("\n");
}
```

```text
========== Unsigned Multiplication Overflow ==========
Using unsigned short (16 bits), Max value: 65535

Multiplying: 544 * 566 = 45760 (truncated from 307904)

Operand a:
Decimal:    544 | Hex: 0x0220 | Binary: 0000 0010 0010 0000

Operand b:
Decimal:    566 | Hex: 0x0236 | Binary: 0000 0010 0011 0110

Full 32-bit product:
Decimal:     307904 | Hex: 0x0004B2C0 | Binary: 0000 0000 0000 0100 1011 0010 1100 0000

Truncated to 16 bits (only lower half):
Decimal:  45760 | Hex: 0xB2C0 | Binary: 1011 0010 1100 0000
```

可以看到，在上述的实验中，两个 `unsigned short` 类型的整数在相乘时必须要使用一个 `unsigned int` 类型的整数来表示，但是最高位的 16 位被截断了，导致 Overflow 的数变小，最终仍然在 `unsigned short` 的范围中。

#### Signed Multiplications in C

和加法类似，有符号整数的乘法依然在比特位上保持相同的计算原则。

- 考虑 $w$ 位的截断原则，两种方法计算出来的数是**完全相同**的。
- 但是考虑**全精度乘法**，**符号扩展**会导致两者的计算结果出现差异。

> [!IMPORTANT]
> 这个差异严格的表述是 相同的二进制位模式（Bit Pattern），在不同的**“解释规则”（编码语义）**下，进行全精度乘法运算得到的二进制结果不一致。CPU 是直接在位上进行运算的，会提供 `MUL`（无符号乘法指令）和 `IMUL`（有符号乘法指令）两套指令集。
> 产生差异的关键在于**整数向高位的补全机制不同**。具体的证明见 [这个章节](#expanding-and-truncating)。因为对最高位的权重解释不相同，最终计算得到的数字结果也完全不同。

```c
void show_signed_vs_unsigned_multiplication() {
  unsigned short us_a = 0xEA61;
  unsigned short us_b = 0xD430;
  unsigned int us_result = (unsigned int)us_a * us_b;

  // 实际会产生溢出行为 但是使用十六进制的字面量来避免编译器警告
  short s_a = 0xEA61;
  short s_b = 0xD430;
  int s_result = (int)s_a * s_b;

  printf("UNSIGNED INTERPRETATION:\n");
  printf("Operand a (as unsigned):\n");
  print_ushort_binary(us_a);
  printf("\nOperand b (as unsigned):\n");
  print_ushort_binary(us_b);
  printf("\nExtended to 32-bit (zero extension):\n");
  print_uint_binary((unsigned int)us_a);
  printf("\nFull 32-bit product:\n");
  print_uint_binary(us_result);
  printf("\n");

  printf("SIGNED INTERPRETATION:\n");
  printf("Operand a (as signed):\n");
  print_short_binary(s_a);
  printf("\nOperand b (as signed):\n");
  print_short_binary(s_b);
  printf("\nExtended to 32-bit (SIGN extension):\n");
  print_int_binary((int)s_a);
  printf("\nFull 32-bit product:\n");
  print_int_binary(s_result);
  printf("\n");
}
```

```text
UNSIGNED INTERPRETATION:
Operand a (as unsigned):
Decimal:  60001 | Hex: 0xEA61 | Binary: 1110 1010 0110 0001

Operand b (as unsigned):
Decimal:  54320 | Hex: 0xD430 | Binary: 1101 0100 0011 0000

Extended to 32-bit (zero extension):
Decimal:      60001 | Hex: 0x0000EA61 | Binary: 0000 0000 0000 0000  | 1110 1010 0110 0001

Full 32-bit product:
Decimal: 3259254320 | Hex: 0xC2444630 | Binary: 1100 0010 0100 0100  | 0100 0110 0011 0000

SIGNED INTERPRETATION:
Operand a (as signed):
Decimal:  -5535 | Hex: 0xEA61 | Binary: 1110 1010 0110 0001

Operand b (as signed):
Decimal: -11216 | Hex: 0xD430 | Binary: 1101 0100 0011 0000

Extended to 32-bit (SIGN extension):
Decimal:       -5535 | Hex: 0xFFFFEA61 | Binary: 1111 1111 1111 1111  | 1110 1010 0110 0001

Full 32-bit product:
Decimal:    62080560 | Hex: 0x03B34630 | Binary: 0000 0011 1011 0011  | 0100 0110 0011 0000
```

可以看到，进行全精度乘法，相同的二进制数计算得到的结果在低位的结果相同，但是在高位的结果完全不同（`1100 0010 0100 0100` and `0000 0011 1011 0011`）

我们可以用简单的代数来解释。假设 $A$ 是原始 16 位模式（0xEA61），其无符号值为 $U$，有符号值为 $S = U - 2^{16}$。同理，$B$ 的无符号值为 $V$，有符号值为 $T = V - 2^{16}$。

- 无符号： $U \times V$
- 有符号： $(U - 2^{16}) \times (V - 2^{16}) = U \times V - 2^{16}(U + V) + 2^{32}$。在 32 位运算的范围内（$\pmod{2^{32}}$），那个 $2^{32}$ 会消失。所以：$$\text{有符号结果} = \text{无符号结果} - 2^{16} \times (U + V)$$

代入上面的式子验证：

```c
printf("The sum value of two original unsigned values:\n");
unsigned short us_add_result = us_a + us_b;
print_ushort_binary(us_add_result);
printf("The diff of multiplication result (Full 32-bit product):\n");
unsigned int diff = us_result - s_result;
for (int i = 31; i >= 0; i--) {
  printf("%d", (diff >> i) & 1);
  if (i % 4 == 0 && i != 0) {
    printf(" ");
  }
  if (i % 16 == 0 && i != 0) {
    printf("| ");
  }
}
printf("\n");
```

```text
The sum value of two original unsigned values:
Decimal:  48785 | Hex: 0xBE91 | Binary: 1011 1110 1001 0001
The diff of multiplication result (Full 32-bit product):
1011 1110 1001 0001 | 0000 0000 0000 0000
```

可以看到，全精度乘法的相差结果（无符号-有符号）正好是 $U+V$ 移动 16 位的结果！

#### Power-of-2 Multiply with Shift

受益于整数的二进制表示，*$2^w$ 的乘法往往会更加快速，因为从比特位的视角来看，只需要将对应的二进制数进行移位操作。（有符号整数和无符号整数都是如此）

#### Unsigned (Signed) Power-of-2 Divide with Shift

同样，对应 $u >> k$ gives $\lfloor \frac{u}{2^k} \rfloor$。这就意味着会有 $k$ 位会被移位到小数点后，对于整数乘法，这些会被抛弃，因此是**向下取整**。

对于有符号整数，情况会略显复杂，在有符号运算中，右移使用的是算术右移，即高位补**符号位**（Sign Extension）。无论正负，它的数学本质始终是：

$$x >> k = \lfloor \frac{x}{2^k} \rfloor$$

这意味着结果总是向数轴左侧（负无穷方向）靠拢。

如果你希望通过移位来模拟逻辑上的除法（即 $-5 / 2 = -2$），你需要对负数进行**偏置**（Biasing）处理。逻辑是：如果在右移前，被除数是负数，则先给它加上 $2^k - 1$ 的偏移量，再执行移位。数学表达式为：$$(x < 0 ? (x + (1 << k) - 1) : x) >> k$$

### Summary

总结：算数运算（乘法和加法）对不同类型的整数（有符号和无符号）在计算机底层上的运算差异：

![Summary](assets/Lecture2/summary.png)

> 从数学上看，计算机丢弃高比特位的截断行为等同于**模运算**。

#### Addition

* **位级一致性：** 无论是有符号数（补码）还是无符号数，在底层的**二进制加法操作是完全一样循环的**。
* **无符号加法：** 结果是 $ (x + y) \text{ mod } 2^w $。
  * 如果和太大，就减去 $2^w$（相当于舍弃进位）。
* **有符号加法：** 结果会经过“修正”以落入正确的正负数范围。
  * 可能会通过加上或减去 $2^w$ 来处理正溢出或负溢出。


#### Multiplication

* **位级一致性：** 同样的，无论是有符号还是无符号，底层的乘法位运算逻辑是一样的。
* **无符号乘法：** 直接取数学乘积结果的低 $w$ 位。
* **有符号乘法：** 将数学乘积的结果**截断**后，按照补码规则重新解释为有符号数。

## Representations in Memory, Pointers and Strings

### Byte-Oriented Memory Organizations

这是最基础的组织方式。在这种模式下，内存被看作一个巨大的字节数组。寻址的最小单位是 **1 字节** (8 bits)。地址从 0, 1, 2, 3... 依次递增，每个地址严格对应一个**字节**。

### Word-Oriented Memory Organizations

计算机程序的运行依赖于**内存地址**的**寻址**操作。内存寻址的最小单位始终是 1 个字节（8 位）。并且操作系统提供了一种抽象，可以将虚拟内存视为一个非常大的数组（页表，内存管理单元）。CPU 读取数据不会一个字节一个字节的读入，而是以**字长**的规模进行成块的搬运，对于一个字长为 $w$-bit 的系统，CPU 可以一次性读入 $\frac{w}{8}$ 个字节。

在一个 $w$ 位的计算机系统中，CPU 内部的寄存器（Register）宽度就是 $w$ 位。例如在 C 语言中，寻址操作是通过**指针**来实现的，为了和寄存器的宽度对齐，指针的长度也被设计位 $w$ 位。因此，对于一个 $w$ 位的计算机系统，内存寻址需要 $w$ 位的二进制数来表示，因此虚拟内存数组的最大长度是 $2^w$。（对于 64 位的数组，$2^{64}$ Bytes是一个非常夸张的天文数字）

> 指针长度和寄存器容量设置严格相等是一方面保证性能（一个指针可以被一次性的加载到寄存器中），另一方面是保证简洁性（寄存器非常昂贵，没有空间上的浪费）

> 在计算机底层中，**对齐**是非常重要的。

## Byte Ordering

简单来说，字节序（Byte Ordering） 决定了计算机如何在内存中排列多字节数据（如整数、浮点数）。

想象你要把一个十六进制数 0x12345678 存进内存。这个数字由 4 个字节组成：12、34、56 和 78。其中 12 是高位（最重头的部分），78 是低位（最小的部分）。

### Big Endian

大端序遵循“人类直觉”：将高位字节存储在起始地址（低地址）。地址从小到大，数据从高位到低位存储。主要用于网络传输协议（TCP/IP 被称为网络字节序）以及某些特定处理器（如传统的 PowerPC）。

### Little Endian

小端序则相反：将低位字节存储在起始地址（低地址）。地址从小到大，数据从低位到高位存储。**注意内存中的基本单元是字节**，对于字节内部比特位的顺序是不会倒过来的。

例如，对于一个 4 字节的值：`0x01234567`:

- Big Endian: `|01|23|45|67|`
- Little Endian: `|67|45|23|01|`

```c
#include <stddef.h>
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

void show_bytes_2(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    printf("%p\t0x%.2x\n", start + i, start[i]);
  }
}

void show_int(int x) { show_bytes((byte_pointer)&x, sizeof(int)); }

void show_float(float x) { show_bytes((byte_pointer)&x, sizeof(float)); }

void show_pointer(void *x) { show_bytes((byte_pointer)&x, sizeof(void *)); }

void show_int_2(int x) { show_bytes_2((byte_pointer)&x, sizeof(int)); }

void show_float_2(float x) { show_bytes_2((byte_pointer)&x, sizeof(float)); }

void show_pointer_2(void *x) { show_bytes_2((byte_pointer)&x, sizeof(void *)); }

int demo_1() {
  show_int(10);
  show_int(10000000);
  int a = 100;
  show_pointer(&a);
  show_float(100);
  show_float(100.0);
  return 0;
}

int demo_2() {
  show_int_2(10);
  show_int_2(10000000);
  int a = 100;
  show_pointer_2(&a);
  show_float_2(100);
  show_float_2(100.0);
  return 0;
}

int main() {
  demo_1();
  demo_2();
  return 0;
}
```

```text
0a 00 00 00
80 96 98 00
6c 63 73 6f 01 00 00 00
00 00 c8 42
00 00 c8 42

# 可以看到，高位的字节在内存中的地址反而更靠前，说明是小端序
0x16f73634c     0x0a
0x16f73634d     0x00
0x16f73634e     0x00
0x16f73634f     0x00
0x16f73634c     0x80
0x16f73634d     0x96
0x16f73634e     0x98
0x16f73634f     0x00
0x16f736348     0x6c
0x16f736349     0x63
0x16f73634a     0x73
0x16f73634b     0x6f
0x16f73634c     0x01
0x16f73634d     0x00
0x16f73634e     0x00
0x16f73634f     0x00
0x16f73634c     0x00
0x16f73634d     0x00
0x16f73634e     0xc8
0x16f73634f     0x42
0x16f73634c     0x00
0x16f73634d     0x00
0x16f73634e     0xc8
0x16f73634f     0x42
```

## Representing Strings

在 C 语言中，字符串可以看成是一个 char 数组，当然也可以看成一个指向 char 的指针。为了能让字符串正确的终止，字符串的最后一个字符必须是 `\0`。

```c
#include <stdio.h>
#include <string.h>

void print_char_array(const char *str) {
  printf("  Address: %p\n", (void *)str);
  printf("  Content: \"%s\"\n", str);
  printf("  Bytes  : ");

  for (int i = 0;; i++) {
    if (str[i] == '\0') {
      printf("'\\0' ");
      break;
    }
    printf("%c           ", str[i]);
  }
  printf("\n");
  printf("  Pointer: ");

  for (int i = 0;; i++) {
    printf("%2p ", str + i);
    if (str[i] == '\0') {
      break;
    }
  }
  printf("\n\n");
}

void show_string_memory_layout() {
  printf("========================================\n");
  printf("String Memory Layout in C\n");
  printf("========================================\n\n");

  char *str1 = "Hello";
  char str2[] = "World";
  char str3[] = {'C', ' ', 'S', 't', 'r', 'i', 'n', 'g', '\0'};

  print_char_array(str1);
  print_char_array(str2);
  print_char_array(str3);
}

int main() {
  show_string_memory_layout();
  return 0;
}
```

```text
========================================
String Memory Layout in C
========================================

  Address: 0x10455476e
  Content: "Hello"
  Bytes  : H           e           l           l           o           '\0' 
  Pointer: 0x10455476e 0x10455476f 0x104554770 0x104554771 0x104554772 0x104554773 

  Address: 0x16b8aa368
  Content: "World"
  Bytes  : W           o           r           l           d           '\0' 
  Pointer: 0x16b8aa368 0x16b8aa369 0x16b8aa36a 0x16b8aa36b 0x16b8aa36c 0x16b8aa36d 

  Address: 0x16b8aa378
  Content: "C String"
  Bytes  : C                       S           t           r           i           n           g           '\0' 
  Pointer: 0x16b8aa378 0x16b8aa379 0x16b8aa37a 0x16b8aa37b 0x16b8aa37c 0x16b8aa37d 0x16b8aa37e 0x16b8aa37f 0x16b8aa380 
```

## Puzzles

### `(x|-x) >> 31 == -1`

```c
#include <limits.h>
#include <stdio.h>

int forward_tmp(int x) { return (x | -x); }
int forward(int x) { return forward_tmp(x) >> 31; }
void test(int x) {
  printf("The value of the forward functions of %d is %d\n", x, forward(x));
}

int main() {
  int candidates[] = {1, -1, 2, 100, -100, 0, INT_MAX, INT_MIN};
  int length = sizeof(candidates) / sizeof(candidates[0]);
  for (int i = 0; i < length; i++) {
    int candidate = candidates[i];
    test(candidate);
  }
}
```

```text
The value of the forward functions of 1 is -1
The value of the forward functions of -1 is -1
The value of the forward functions of 2 is -1
The value of the forward functions of 100 is -1
The value of the forward functions of -100 is -1
The value of the forward functions of 0 is 0
The value of the forward functions of 2147483647 is -1
The value of the forward functions of -2147483648 is -1
```

- 如果 $x > 0$：$x$ 的符号位是 0，而 $-x$ 的符号位是 1。按位或（OR）之后，符号位必然是 1。
- 如果 $x < 0$：$x$ 的符号位是 1，$-x$ 的符号位（通常）是 0。按位或之后，符号位必然是 1。
- 如果 $x = 0$：$0$ 的原码和补码都是全 0，$-0$ 也是全 0。按位或之后，符号位依然是 0。结论： 只要 $x \neq 0$，(x | -x) 的最高位（符号位）就一定是 1。

在移位 31 位之后，只有算数位一致保留，对于前两种情况，移位后的结果是全 1（移位的时候和符号位保持一致）只有 0 依然保持全 0。

Bit Hack 的艺术真奇妙。