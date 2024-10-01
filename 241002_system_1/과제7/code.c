#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("test.txt", O_RDWR);
  char txt[2001];
  size_t bytesread;

  bytesread = read(fd, txt, 2000);
  txt[bytesread] = '\0';

  int lineCnt = 1;
  char* line = strtok(txt, "\n");
  while (line) {
    printf("%3d: %s\n", lineCnt, line);
    line[strlen(line)] = '\n';
    lineCnt++;
    line = strtok(NULL, "\n");
  }

  printf("line number to erase: ");
  int target;
  scanf("%d", &target);

  lseek(fd, 0, SEEK_SET);
  ftruncate(fd, 0);

  line = strtok(txt, "\n");
  lineCnt = 1;
  while (line) {
    if (lineCnt != target) {
      write(fd, line, strlen(line));
      write(fd, "\n", 1);
    }
    line = strtok(NULL, "\n");
    lineCnt++;
  }

  printf("file saved.\n");

  return 0;
}
