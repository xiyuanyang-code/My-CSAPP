long pcount_do(unsigned long x) {
  // 计算一个无符号整数的二进制中 1 的数量（汉明重量）
  long result = 0;
  do {
    result += (x & 0x1);
    x >>= 1;
  } while (x);
  return result;
}

long pcount_goto(unsigned long x) {
  long result = 0;
loop:
  result += x & 0x1;
  x >>= 1;
  if (x) {
    goto loop;
  }
  return result;
}
