#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  int fd = open("num.txt", O_RDONLY);
  char str[10];
  read(fd, str, 10);
  int num = atoi(str);
  printf("num + 10 = %d\n", num + 10);
  return 0;
}
