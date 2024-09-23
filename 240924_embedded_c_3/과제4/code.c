#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  const char* vect = "DATA|32ALL|0|200|100|ABABC|200";
  char vectarr[50];
  sprintf(vectarr, "%s", vect);
  char* p = strtok(vectarr, "|");
  int sum = 0;
  char* others[10];
  size_t otherCnt = 0;

  while (p) {
    // 숫자인지 검사
    int isNumber = 1;
    char* c = p;
    while (*c) {
      if (*c > '9') {
        isNumber = 0;
        break;
      }
      c++;
    }
    if (isNumber) {
      int value = strtol(p, NULL, 10);
      sum += value;
    } else {
      others[otherCnt++] = p;
    }
    p = strtok(NULL, "|");
  }

  printf("sum : %d\n", sum);
  printf("other : ");
  for (int i = 0; i < otherCnt; i++) {
    printf("%s", others[i]);
    if (i != otherCnt - 1) printf("|");
  }

  return 0;
}
