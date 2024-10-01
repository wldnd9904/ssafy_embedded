#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  int fd = open("read.txt", O_RDONLY);
  char input[11];
  size_t bytesread;
  int lineCnt = 1;
  while (bytesread = read(fd, input, 10)) {
    input[bytesread] = '\0';
    printf("%3d: %s ... %d\n", lineCnt++, input, bytesread);
  }
  return 0;
}
