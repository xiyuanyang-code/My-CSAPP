long absdiff(long x, long y) {
  long result;
  if (x > y) {
    result = x - y;
  } else {
    result = y - x;
  }
  return result;
}

long abs_diff_j(long x, long y) {
  long result;
  int n_test = x <= y;
  if (n_test) {
    goto Else;
  }
  result = x - y;
  goto Done;
Else:
  result = y - x;
Done:
  return result;
}

long abs_diff_complex(long x, long y) {
  long result;
  long diff = x - y;
  if (diff > 5) {
    result = diff + 5;
  } else if (diff > 0) {
    result = diff;
  } else {
    result = -diff;
  }

  return result;
}

long abs_diff_complex_switch(long x, long y) {
  long result;
  long diff = x - y;
  switch (diff) {
  case 10:
    result = diff + 10;
    return result;
    break;
  case 5:
    result = diff + 5;
    return result;
    break;
  case 0:
    result = diff + 0;
    return result;
  default:
    result = diff;
    return result;
  }
}

long abs_diff_complex_no_switch(long x, long y) {
  long result;
  long diff = x - y;
  if (diff == 10) {
    result = diff + 10;
    return result;
  } else if (diff == 5) {
    result = diff + 5;
    return result;
  } else if (diff == 0) {
    result = diff + 0;
    return result;
  } else {
    result = diff;
    return result;
  }
}
