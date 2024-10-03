#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t mypid;
  pid_t childpid = fork();

  if (childpid != 0) {
    mypid = getpid();
    printf("[%u] I'm Parent! I'm Busy!!\n", mypid);
    while (1);
  } else {
    mypid = getpid();
    printf("[%u] Hi! I'm baby! ByeBye\n", mypid);

    childpid = fork();

    if (childpid != 0) {
      printf("[%u] Grow Up!\n", mypid);
      while (1);
    } else {
      mypid = getpid();
      printf("[%u] I'm Groot!\n", mypid);
      return 0;
    }
  }

  return 0;
}
