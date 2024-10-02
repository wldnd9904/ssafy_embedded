#include <stdio.h>
#include <string.h>

#include "run.h"

int main() {
  char command[10];
  init();
  while (1) {
    printf("ssafy >> ");
    fgets(command, sizeof(command), stdin);

    // Remove newline character from command
    command[strcspn(command, "\n")] = '\0';

    if (strcmp(command, "") == 0) {
      // If the command is empty (i.e., user just pressed Enter), skip the
      // iteration
      continue;
    }

    if (strcmp(command, "show") == 0) {
      show();
    } else if (strcmp(command, "add") == 0) {
      /* printf("add\n");*/
      add();
    } else if (strcmp(command, "del") == 0) {
      /*printf("del\n");*/
      del();
    } else {
      printf("Unknown command\n");
    }
  }
  return 0;
}

