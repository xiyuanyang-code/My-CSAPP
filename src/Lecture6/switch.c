long switch_eg(long x, long y, long z) {
  long w = 1;
  switch (z) {
  case 1:
    w = y * z;
    break;
  case 2:
    w = y / z;
    // Fall through
  case 3:
    w += z;
    break;
  case 5:
  case 6:
    w -= z;
    break;
  default:
    w = 2;
  }
  return w;
}

long switch_eg_jump_table(long x, long y, long z) {
    long w = 1;
    /* 增加分支数量并保持连续性，强制触发跳转表优化 */
    switch (z) {
        case 100:
            w = y * z;
            break;
        case 101:
            w = y / z;
            // Fall through
        case 102:
            w += z;
            break;
        case 103:
            w = y - z;
            break;
        case 104:
        case 105:
            w -= z;
            break;
        case 106:
            w = x >> 2;
            break;
        default:
            w = 2;
    }
    return w;
}