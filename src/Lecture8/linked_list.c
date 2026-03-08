#include <stddef.h>
struct rec {
  size_t i;
  int a[4];
  struct rec *next;
};

void set_val(struct rec *r, int val) {
  while (r) {
    int i = r->i;
    r->a[i] = val;
    r = r->next;
  }
}