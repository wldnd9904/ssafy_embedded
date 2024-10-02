#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void* run(void* arg) {
  int id = *(int*)arg;
  printf("%d ", id);
}

int main() {
  int id[37];
  pthread_t pt[37];
  for (int i = 0; i < 37; i++) {
    id[i] = i + 1;
    pthread_create(&pt[i], NULL, run, &id[i]);
  }
  for (int i = 0; i < 37; i++) pthread_join(pt[i], NULL);
  printf("VVCC END");
  return 0;
}
