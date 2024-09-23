#include <stdio.h>
#include <string.h>

void insertStr(char* dest, char* src, char* str, size_t pos) {
  int strSize = strlen(str);
  strncpy(dest, src, pos);
  strcpy(dest + pos, str);
  strcpy(dest + pos + strSize, src + pos);
}

int main() {
  char vect[10] = "ZXXVQ";
  char result[10];
  insertStr(result, vect, "ABC", 2);
  printf("%s", result);
  return 0;
}
