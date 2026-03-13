#include <stddef.h>
#define IDENT 1
#define OP *
typedef int data_t;
typedef struct {
  size_t len;
  data_t *data;
} vec;

int get_vec_element(vec *v, size_t idx, data_t *val) {
  if (idx >= v->len) {
    return 0;
  }
  *val = v->data[idx];
  return 1;
}

int vec_length(vec *v) { return v->len; }

// benchmark baseline functions
void combine1(vec *v, data_t *dest) {
  long int i;
  *dest = IDENT;
  for (i = 0; i < vec_length(v); i++) {
    data_t val;
    get_vec_element(v, i, &val);
    *dest = *dest OP val;
  }
}