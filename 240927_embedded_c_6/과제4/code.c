#include <stdio.h>

int main() {
  int arr[3][5] = {
      {10, 20, 30, 40, 50},
      {50, 40, 30, 20, 10},
      {10, 30, 50, 70, 90},
  };
  int *p[3][5];

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 5; j++) p[i][j] = &arr[i][j];

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%d ", *p[i][j]);
    }
    printf("\n");
  }
  return 0;
}