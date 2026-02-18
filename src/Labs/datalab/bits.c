/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // * x^y = (x or y) and ~(x & y)
  // *x or y = ~(~x and ~y)
  int x_or_y = ~(~x & ~y);
  return x_or_y & ~(x & y);
}

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // 获得 111...1111 的全 1 二进制数
  int zero = ~0;

  // 右移 31 位，使符号位是 1，其他位全部是 0
  int ans = zero << 31;
  return ans;
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // 检查 x 的二进制补码表示是不是 011111...111
  // 受限对 x 加 1，让其溢出，溢出的结果是 t_min 100000...000
  int should_be_t_min = x + 1;

  // 对两个数做 xor 运算，应该得到全 1（即 -1）
  int should_be_all_ones = should_be_t_min ^ x;

  // 对其反转 得到全 0 的二进制表示
  int should_be_all_zeros = ~should_be_all_ones;

  // !CORNER CASE
  // 如果 x 是 11...1111, +1 之后溢出到全 0 000...000
  // 此时也会满足对应的内容 需要额外考虑 corner case
  int should_be_one = !!should_be_t_min;

  return should_be_one & (!should_be_all_zeros);
}

/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // 思路：生成一个掩码数 0xAAAAAAAA，使用与或运算来判断奇数位的数是否为 0
  // 0xAAAAAAAA: 1010 1010 1010 1010
  // 一种聪明的生成掩码数的方法：移位 & | 运算 相加数位
  int a = 0xAA;               // 10101010
  int a2 = a | (a << 8);      // 10101010 10101010 (0xAAAA)
  int mask = a2 | (a2 << 16); // 0xAAAAAAAA
  int pulled_bits = mask & x;
  return !(pulled_bits ^ mask);
}

/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { return ~x + 1; }

/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // 判断范围转化为判断 x > 0?
  // * 判断符号？移位操作判断符号位即可

  // 判断 x - min
  int lowercheck = x + (~0x30 + 1);
  int sign1 = (lowercheck >> 31) & 1;

  // max - x
  int uppercheck = 0x39 + (~x + 1);
  int sign2 = (uppercheck >> 31) & 1;
  return (!sign1) & (!sign2);
}

/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // 判断 x 是不是 0 生成对应的全零或者全 1 的掩码
  int boolx = !!x;
  int mask = (~boolx + 1);
  // 如果 x 是 0，生成的 mask 是 0
  // 如果 x 不是 0，生成的 mask 是 -1 (all 1 in bits)
  return (mask & y) + ((~mask) & z);
}

/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // 方法 1：使用一个二进制数来表示 diff < 0，使用符号位即可
  // * 减法操作可能导致溢出
  // int diff = y + (~x + 1);
  // int sign = (diff >> 31) & 1;
  // return !sign;

  // * 直接进行 bit-level 的比较
  // * 比较符号位
  int x_sign = (x >> 31) & 1;
  int y_sign = (y >> 31) & 1;

  // 考虑符号位相同和符号位不同两种情况 两个保持一个为真 就可以判定为真
  int case_a = (x_sign ^ y_sign) & x_sign;

  // consider case b
  // * 此时计算不会溢出 直接运算即可
  int diff = y + (~x + 1);
  int diff_sign = (diff >> 31) & 1;
  int case_b = (!(x_sign ^ y_sign)) & !diff_sign;
  return case_a | case_b;
}

// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  // * 基本的数学原理 当 x 不等于 0 的时候，(x|-x) = -1 (二进制为全 1)
  // * 当 x = 0 的时候，上式为 0
  // * 因此 只需要移位判断符号位即可

  int sign = ((x | (~x + 1)) >> 31) & 1;

  // * 一个 trick 和 1 做异或运算可以实现 01 反转
  return 1 ^ sign;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // 找到能表示 x 的最小补码位数
  // 预处理：如果 x 是负数，就对其取反
  // * 题目转化为 需要找到二进制中最高位的 1
  // 因为二进制数是定长的（32 bits），因此使用有限次二分法即可实现
  // * 二分法的核心和关键是比较和不同分支的控制，在上面的 condition 函数已经实现
  int b_16, b_8, b_4, b_2, b_1, b_0;
  int sign = x >> 31;
  // preprocessing
  x = (sign & ~x) | (~sign & x);

  // 如果 x 的最高 16 位中存在 1，则 b_16 为 16，此时需要去高位查找，右移 16 位
  // 反之为 b_16 = 0，此时需要去低位查找（默认不变）
  // 后续的操作只会关注 最低位的 16 位，高位的 16
  // 位不会再关注！（已经保证全部都是 0）

  // 寻找原始的 32 位中最高的 16 位是否包含 1
  b_16 = (!!(x >> 16)) << 4;
  x = x >> b_16;

  // 寻找剩下的 16 位中最高的 8 位是否包含 1
  b_8 = (!!(x >> 8)) << 3;
  x = x >> b_8;

  // 寻找剩下的 8 位中最高的 4 位是否包含 1
  b_4 = (!!(x >> 4)) << 2;
  x = x >> b_4;

  // 寻找剩下的 4 位中最高的 2 位是否包含 1
  b_2 = (!!(x >> 2)) << 1;
  x = x >> b_2;

  // 寻找剩下的 2 位中最高的 1 位是否包含 1
  b_1 = (!!(x >> 1)) << 0;
  x = x >> b_1;

  // 最终只剩下 1 位需要判断，做两次 ! 即可判断是否包含 1
  b_0 = !!x;

  // * 有点二进制表示的思想
  return b_16 + b_8 + b_4 + b_2 + b_1 + b_0 + 1;
}

// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  // * 预处理关键函数 提取一个 32 位 float 的符号位 & 指数位和尾数位

  // * 符号位 右移 31 位 取最后一位
  unsigned s = (uf >> 31) & 1;

  // * 指数位 右移 23 位 取最后八位
  unsigned exp = (uf >> 23) & 0xFF;

  // * 尾数位 取最后 23 位
  unsigned frac = uf & 0x7FFFFF;

  // if it is a special value
  if (exp == 255) {
    return uf;
  }

  // if it is a denormalized value
  if (exp == 0) {
    // * 非规格化数的指数位全部为 0，只需要对尾数位左移 1 位就可以了
    // * 这也是非规格化数的很简洁的设计，实现从规格化数向非规格化数的平滑过渡
    // * s << 31 防止符号位被覆盖
    return (s << 31) | (uf << 1);
  }

  // if it is a normalized value
  // * 一般的操作：指数位+1 即可
  // * 但是要考虑指数位溢出的操作
  exp++;
  if (exp == 255) {
    // 如果溢出了，返回对应符号的无穷大
    return (s << 31) | 0x7F800000;
  }
  return (s << 31) | (exp << 23) | frac;
}

/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned s = (uf >> 31) & 1;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  unsigned E = exp - 127;
  // * M 代表 1.frac 左移位 23 位的结果
  unsigned M = frac | 0x800000;
  // 0x800000: 1000 0000 0000 0000 0000 0000
  // * 选择该掩码的原因是 1 后面跟着尾数的 32 个 0 这样可以把规格化数隐藏的那个
  // 1 补充起来
  // E = exp - 127

  if (exp == 255) {
    // * denormalized values
    return 0x80000000u;
  }

  if (exp < 127) {
    // * 如果归一化前的指数 < 0 转化为 int 会被截断成 0，直接 return 0;
    return 0;
  }

  if (E >= 31) {
    // * 如果原始指数位 > 0 直接处理溢出
    return 0x80000000u;
  }

  if (E > 23) {
    // 如果 E > 23，说明小数点要向右移（即数值扩大），左移位
    M = M << (E - 23);
  } else {
    // 如果 E <= 23，说明小数点在 23 位以内，需要右移抹去小数部分
    M = M >> (23 - E);
  }
  return (s ? -M : M);
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  if (x > 127) {
    return 0x7F800000;
  }

  // * 处理规格化数 最小的 exp 是 1 因此最小的 E 是 1 - 127 = -126
  if (x >= -126) {
    unsigned exp = x + 127;
    // 符号位和 frac 部分都是 0 右移 23 位得到最终的 pow 结果
    return exp << 23;
  }

  // * 处理非规格化数
  // 最小的非规格化数是 2^-149 (-126 + (-23) = -149)
  if (x >= -149) {
    // ! 此时指数位位 0，需要填充 23 位的符号位
    // 当 x = -127 时，我们需要 0.1 (二进制) -> frac 是 1 << 22
    // 当 x = -149 时，我们需要 0.00...1 -> frac 是 1 << 0
    // * 线性的 可以推导出位移公式：23 - (-126 - x) = 23 + 126 + x = 149 + x
    return (1 << (149 + x));
  }

  return 0;
}
