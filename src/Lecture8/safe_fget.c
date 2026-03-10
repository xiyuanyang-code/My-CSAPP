#include <stdio.h>
#include <string.h>

#define MAX_BUF 16

int main() {
  char input_id[MAX_BUF];
  char bio[MAX_BUF];
  char secure_backup[8];

  printf("Enter a String with maximum length of %d: ", MAX_BUF - 1);
  scanf("%15s", input_id);

  // * 清除缓冲区中的回车符
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;

  printf("Enter another string with maximum length of %d: ", MAX_BUF - 1);
  if (fgets(bio, sizeof(bio), stdin) != NULL) {
    bio[strcspn(bio, "\n")] = '\0';
  }

  printf("Using strncpy...\n");
  strncpy(secure_backup, bio, sizeof(secure_backup) - 1);
  secure_backup[sizeof(secure_backup) - 1] = '\0';

  printf("String 1: %s\n", input_id);
  printf("String 2: %s\n", bio);
  printf("String 3: %s\n", secure_backup);

  return 0;
}