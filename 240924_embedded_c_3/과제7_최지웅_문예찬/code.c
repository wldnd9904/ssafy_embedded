#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct message {
  char content[1000];
  struct message* next;
} message;

typedef struct log {
  int month;
  int date;
  int hour;
  int cnt;
  message* head;
} log;

int static compare(const void* a, const void* b) {
  const log* first = *(const log**)a;
  const log* second = *(const log**)b;

  if (first->cnt > second->cnt)
    return -1;
  else if (first->cnt < second->cnt)
    return 1;
  else {
    if (first->month + first->date > second->month + second->date)
      return -1;
    else
      return 1;
  }
  return 0;
}

int main() {
  FILE* fp = fopen("log.txt", "r");
  log* logs[1464];
  int logCnt = -1;
  message* prevMessage;

  for (int i = 0; i < 2000; i++) {
    message* curMessage = malloc(sizeof(message));
    curMessage->next = NULL;
    fgets(curMessage->content, 1000, fp);
    // Jun 17 04:03:36 comb...
    char monthStr[4];
    char dateStr[3];
    char hourStr[10];
    sscanf(curMessage->content, "%s %s %s", monthStr, dateStr, hourStr);
    int curMonth = strcmp(monthStr, "Jul") ? 6 : 7;
    int curDate = atoi(dateStr);
    int curHour = atoi(hourStr);

    if (logCnt >= 0 && (curMonth == logs[logCnt]->month) &&
        (curDate == logs[logCnt]->date) && (curHour == logs[logCnt]->hour)) {
      prevMessage->next = curMessage;
    } else {
      logCnt++;
      logs[logCnt] = malloc(sizeof(log));
      logs[logCnt]->month = curMonth;
      logs[logCnt]->date = curDate;
      logs[logCnt]->hour = curHour;
      logs[logCnt]->cnt = 0;
      logs[logCnt]->head = curMessage;
    }
    logs[logCnt]->cnt++;
    prevMessage = curMessage;
  }
  fclose(fp);

  qsort(logs, logCnt + 1, sizeof(log*), compare);

  for (int i = 0; i < 3; i++) {
    printf("%d %d %d: %d\n", logs[i]->month, logs[i]->date, logs[i]->hour,
           logs[i]->cnt);
    message* cur = logs[i]->head;
    while (cur->next != NULL) cur = cur->next;
    printf("%s\n", cur->content);
  }

  return 0;
}
