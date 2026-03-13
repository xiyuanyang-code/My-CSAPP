#include <stddef.h>
#include <string.h>

void lower(char *s) {
  size_t i;
  for (i = 0; i < strlen(s); i++) {
    // call strlen every time!
    if (s[i] >= 'A' && s[i] <= 'Z') {
      s[i] -= ('A' - 'a');
    }
  }
}
// O(N^2)

void lower_faster(char *s) {
  size_t i;
  size_t length = strlen(s);
  for (i = 0; i < length; i++) {
    // call strlen every time!
    if (s[i] >= 'A' && s[i] <= 'Z') {
      s[i] -= ('A' - 'a');
    }
  }
}
// O(N)