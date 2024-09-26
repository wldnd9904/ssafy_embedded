#include <stdio.h>

int main() {
  int a = 50;
  int b = 70;
  int* arr[2][3] = {{&a, &a, &b}, {&b, &b, &a}};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d ", *arr[i][j]);
    }
    printf("\n");
  }
  return 0;
}