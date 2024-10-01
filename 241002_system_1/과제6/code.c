#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("text.txt", O_RDONLY);
  char input[6];
  size_t bytesread;

  // first 5 characters
  bytesread = read(fd, input, 5);
  input[bytesread] = '\0';
  printf("1: %s\n", input);

  // last 5 characters
  lseek(fd, -6, SEEK_END);
  bytesread = read(fd, input, 5);
  input[bytesread] = '\0';
  printf("2: %s\n", input);

  // 3 characters
  printf("3: \n");
  lseek(fd, 0, SEEK_SET);
  while (bytesread = read(fd, input, 3)) {
    input[bytesread] = '\0';
    printf("%s", input);
    if (strcmp(input, "GHI") == 0) {
      printf(" ... GHI found!\n");
      lseek(fd, 5, SEEK_CUR);
    } else {
      printf("\n");
    }
  }

  return 0;
}
