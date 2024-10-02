#include "run.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _minor {
  pthread_t pth;
  struct _minor* next;
  struct _minor* prev;
} minor;

static pthread_mutex_t lock;
static long long coin;
static minor head;
static int qSize;

static void* plus() {
  while (1) {
    pthread_mutex_lock(&lock);  // Lock the coin value
    coin++;
    pthread_mutex_unlock(&lock);  // Lock the coin value
    usleep(100000);
  }
}

static int enque(pthread_t pth) {
  minor* tmp = malloc(sizeof(minor));
  tmp->pth = pth;
  if (qSize) {
    tmp->prev = head.prev;
    head.prev->next = tmp;
    head.prev = tmp;
  } else {
    head.next = tmp;
    head.prev = tmp;
    tmp->prev = &head;
  }
  tmp->next = &head;
  return ++qSize;
}

static int deque() {
  if (qSize == 0) return 0;
  pthread_cancel(head.prev->pth);
  free(head.prev);
  if (qSize == 1) {
    head.next = NULL;
    head.prev = NULL;
  } else {
    head.prev = head.prev->prev;
    head.prev->prev->next = &head;
  }
  return --qSize;
}

void init() {
  pthread_mutex_init(&lock, NULL);
  coin = 0;
  qSize = 0;
}

void show() {
  printf("current coin: %lld\n", coin);
  printf("current minors: %d\n", qSize);
}

void add() {
  pthread_t pth;
  pthread_create(&pth, NULL, plus, NULL);
  int minorsLeft = enque(pth);
  printf("minor added. current minors: %d\n", minorsLeft);
}

void del() {
  int minorsLeft = deque();
  printf("minor deleted. current minors: %d\n", minorsLeft);
}
