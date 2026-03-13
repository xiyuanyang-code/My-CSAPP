void set_row(double *a, double *b, long i, long n) {
  long j;
  for (j = 0; j < n; j++) {
    a[n * i + j] = b[j];
  }
}

void set_row_licm(double *a, double *b, long i, long n) {
  long j;
  long ni = n * i;
  double *rowp = a + ni;
  for (j = 0; j < n; j++) {
    // faster :)
    *rowp++ = b[j];
  }
}

void set_value(double *a, double *b, long n) {
  long i, j;
  for (i = 0; i < n; i++) {
    // 每次都要进行昂贵的乘法操作
    long ni = n * i;
    for (j = 0; j < n; j++) {
      a[ni + j] = b[j];
    }
  }
}

void set_value_faster(double *a, double *b, long n) {
  long i, j;
  long ni = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      a[ni + j] = b[j];
    }
    // 转化为加法操作 :)
    ni += n;
  }
}