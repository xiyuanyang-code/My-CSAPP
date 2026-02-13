#include <stdio.h>
#include <string.h>

void print_char_array(const char *str) {
  printf("  Address: %p\n", (void *)str);
  printf("  Content: \"%s\"\n", str);
  printf("  Bytes  : ");

  for (int i = 0;; i++) {
    if (str[i] == '\0') {
      printf("'\\0' ");
      break;
    }
    printf("%c           ", str[i]);
  }
  printf("\n");
  printf("  Pointer: ");

  for (int i = 0;; i++) {
    printf("%2p ", str + i);
    if (str[i] == '\0') {
      break;
    }
  }
  printf("\n\n");
}

void show_string_memory_layout() {
  printf("========================================\n");
  printf("String Memory Layout in C\n");
  printf("========================================\n\n");

  char *str1 = "Hello";
  char str2[] = "World";
  char str3[] = {'C', ' ', 'S', 't', 'r', 'i', 'n', 'g', '\0'};

  print_char_array(str1);
  print_char_array(str2);
  print_char_array(str3);
}

int main() {
  show_string_memory_layout();
  return 0;
}
