#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
  int fd = open("cal.txt", O_RDWR);
  char str[10];
  size_t bytesread = read(fd, str, 10);
  str[bytesread] = '\0';
  printf("%s\n", str);
  int num = atoi(str);
  ftruncate(fd, 0);
  lseek(fd, 0, SEEK_SET);
  printf("num: %d\n", num);
  sprintf(str, "%d", num * 2);
  write(fd, str, strlen(str));
  return 0;
}
