#include <stdio.h>
char *unsafe_gets(char *dest) {
  // * 工作指针 p 指向缓冲区的起始位置

  int c = getchar();
  char *p = dest;
  while (c != EOF && c != '\n') {
    *p++ = c;
    // * 先自增、但是解引用的是自增之前的地址
    c = getchar();
  }
  *p = '\0';
  return dest;
  // * 最终 dest 指向的是缓冲区的起始位置的指针
}

char *safe_gets(char *dest, int size) {
  int c = getchar();
  char *p = dest;
  int count = 0;
  // 增加了一个条件：count < size - 1
  // * 避免读入的字符超过缓冲区
  while (count < size - 1 && c != EOF && c != '\n') {
    *p++ = c;
    count++;
    c = getchar();
  }
  *p = '\0';
  return dest;
}

int main(){
    char buffer[16];
    // ! unsafe methods
    printf("%s\n", unsafe_gets(buffer));

    // safe methods
    printf("%s\n", safe_gets(buffer, sizeof(buffer)));
    return 0;
}