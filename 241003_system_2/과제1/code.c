#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void* run1(void* arg) {
  int id = *(int*)arg;
  int cnt = 0;
  while (1) {
    printf("[DD%d] %c\n", id, 'A' + cnt);
    cnt++;
    cnt %= 3;
    usleep(300);
  }
}

void* run2(void* arg) {
  int id = *(int*)arg;
  int cnt = 0;
  while (1) {
    printf("[DD%d] %d\n", id, cnt);
    cnt++;
    cnt %= 6;
    usleep(200);
  }
}

void* run3(void* arg) {
  int id = *(int*)arg;
  int cnt = 0;
  while (1) {
    printf("[DD%d] %c\n", id, 'A' + cnt);
    cnt++;
    cnt %= 27;
    usleep(300);
  }
}

int main() {
  int id[3] = {1, 2, 3};
  pthread_t pt[3];
  pthread_create(&pt[0], NULL, run1, &id[0]);
  pthread_create(&pt[1], NULL, run2, &id[1]);
  pthread_create(&pt[2], NULL, run3, &id[2]);
  for (int i = 0; i < 3; i++) pthread_join(pt[i], NULL);
  return 0;
}
