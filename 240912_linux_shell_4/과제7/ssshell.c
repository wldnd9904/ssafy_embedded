#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HISTORY 3000
#define MAX_COMMAND 20

char commands[MAX_HISTORY][MAX_COMMAND];
int commandCnt = 1;

void printHistory() {
  for (int i = 1; i <= commandCnt; i++) {
    printf("%d\t%s\n", i, commands[i]);
  }
}

int parseIntFromCommand(int commandIdx) {
  if (commands[commandIdx][1] < '0' || commands[commandIdx][1] > '9') return -1;
  int base = commands[commandIdx][1] - '0';
  int i = 2;

  char cur;
  while ((cur = commands[commandIdx][i]) != '\0') {
    if (cur < '0' || cur > '9') return -1;

    base *= 10;
    base += cur - '0';
    i++;
  }
  return base;
}

void process(int commandIdx) {
  if (strcmp(commands[commandIdx], "date") == 0)
    system("date");
  else if (strcmp(commands[commandIdx], "uptime") == 0)
    system("uptime");
  else if (strcmp(commands[commandIdx], "ls") == 0)
    system("ls -al");
  else if (strcmp(commands[commandIdx], "log") == 0)
    system("dmesg");
  else if (strcmp(commands[commandIdx], "history") == 0)
    printHistory();
  else if (strcmp(commands[commandIdx], "hclear") == 0)
    commandCnt = 0;
  else if (commands[commandIdx][0] == '!') {
    int idx = parseIntFromCommand(commandIdx);
    if (idx < 0 || idx >= commandCnt) {
      printf("ERROR: wrong history index!\n");
      commandCnt = commandIdx - 1;
    } else {
      for (int i = 0; i < MAX_COMMAND; i++) {
        commands[commandIdx][i] = commands[idx][i];
      }
      process(idx);
    }
  } else
    printf("ERROR\n");
}

int prompt() {
  printf("SSAFY > ");
  int i = 0;
  while (i < MAX_COMMAND) {
    char input = getchar();
    if (input == '\n') break;
    commands[commandCnt][i] = input;
    ++i;
  }
  if (i == 0) return 0;
  if (i == MAX_COMMAND) {
    while (getchar() != '\n') printf("입력버퍼 비우는 중...\n");
    return 0;
  }
  commands[commandCnt][i] = '\0';

  if (strcmp(commands[commandCnt], "exit") == 0) return 1;
  process(commandCnt);
  ++commandCnt;
  return 0;
}

int main() {
  while (commandCnt < MAX_HISTORY) {
    int result = prompt();
    if (result) break;
  }

  return 0;
}
