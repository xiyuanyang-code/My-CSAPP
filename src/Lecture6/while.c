long pcount_while(unsigned long x) {
  long result = 0;
  while (x) {
    result += x & 0x1;
    x >>= 1;
  }
  return result;
}

// equal version of goto versions
// * jump to middle versions
long pcount_goto_jtm(unsigned long x) {
  long result = 0;
  goto test;
loop:
  result += x & 0x1;
  x >>= 1;
test:
  if (x) {
    goto loop;
  }
  return result;
}

// * do-while versions
long pcount_goto_dw(unsigned long x) {
  long result = 0;
  // 相当于 do-while 加了一个前置判断
  if (!x) {
    goto done;
  }
loop:
  result += (x & 0x1);
  x >>= 1;
  if (x) {
    goto loop;
  }

done:
  return result;
}