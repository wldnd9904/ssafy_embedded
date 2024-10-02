#include <pthread.h>
#include <stdio.h>

void* abc(void* arg) {
  int id = *(int*)arg;
  switch (id) {
    case 1:
      printf("1 ABC\n");
      break;
    case 2:
      printf("2 MINMIN\n");
      break;
    case 3:
      printf("3 COCO\n");
      break;
    case 4:
      printf("4 KFCKFC\n");
      break;
  }
}

int main() {
  int id[4];
  pthread_t pt[4];
  for (int i = 0; i < 4; i++) {
    id[i] = i + 1;
    pthread_create(&pt[i], NULL, abc, &id[i]);
  }
  for (int i = 0; i < 4; i++) {
    pthread_join(pt[i], NULL);
  }
  return 0;
}
