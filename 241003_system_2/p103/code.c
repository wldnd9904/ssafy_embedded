#include <pthread.h>  // POSIX 스레드 라이브러리 포함
#include <stdio.h>    // 표준 입출력 라이브러리 포함

pthread_mutex_t mlock;  // 뮤텍스 선언
int cnt = 0;            // 전역 변수 cnt 초기화

// 스레드가 실행할 함수
void *run() {
  // 뮤텍스 잠금
  pthread_mutex_lock(&mlock);

  // cnt를 10000번 증가 critical section
  for (int i = 0; i < 10000; i++) cnt++;

  // 뮤텍스 잠금 해제
  pthread_mutex_unlock(&mlock);
}

int main() {
  // 뮤텍스 초기화
  pthread_mutex_init(&mlock, NULL);
  pthread_t tid[4];  // 스레드 ID를 저장할 배열 선언

  // 4개의 스레드 생성
  for (int i = 0; i < 4; i++) pthread_create(&tid[i], NULL, run, NULL);

  // 생성된 4개의 스레드가 종료될 때까지 대기
  for (int i = 0; i < 4; i++) pthread_join(tid[i], NULL);

  // cnt 값 출력
  printf("%d\n", cnt);

  // 뮤텍스 소멸
  pthread_mutex_destroy(&mlock);

  return 0;
}