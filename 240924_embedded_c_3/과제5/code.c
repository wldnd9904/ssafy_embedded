#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char vect[100] = "DBABCCQABC";
  char tar[4] = "ABC";
  const size_t tarSize = strlen(tar);
  char* p = strstr(vect, tar);
  while (p) {
    strcpy(p, p + tarSize);
    p = strstr(p, tar);
  }
  printf("%s", vect);
  return 0;
}
