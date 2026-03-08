#include <stddef.h>
struct rec {
  size_t i;
  int a[4];
  struct rec *next;
};

int get_a(struct rec *r, size_t idx) { return r->a[idx]; }

int *get_ap(struct rec *r, size_t idx) { return &(r->a[idx]); }