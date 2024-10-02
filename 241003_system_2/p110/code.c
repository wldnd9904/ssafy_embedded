#include <pthread.h>  // POSIX 스레드 라이브러리 포함
#include <stdio.h>    // 표준 입출력 라이브러리 포함
#include <unistd.h>  // 유닉스 표준 기능 포함 (sleep 함수 사용을 위해 포함)

// 첫 번째 스레드가 실행할 함수
void *abc(void *arg) {
  while (1) {              // 무한 루프
    printf("[T1] BTS\n");  // "BTS" 문자열 출력 (스레드 1)
    sleep(1);              // 1초 동안 대기
  }
}

// 두 번째 스레드가 실행할 함수
void *killABC(void *arg) {
  int count = 0;  // 카운터 변수 초기화

  while (count < 10) {           // 카운터가 10이 될 때까지 반복
    count++;                     // 카운터 증가
    printf("[T2] %d\n", count);  // 현재 카운터 값을 출력 (스레드 2)
    sleep(1);                    // 1초 동안 대기
  }

  printf("Thread1 Kill\n");  // 스레드 1을 종료하기 전에 메시지 출력
  pthread_cancel(*(pthread_t *)arg);  // 스레드 1을 종료
}

int main() {
  setbuf(stdout, NULL);  // 표준 출력 버퍼를 비활성화하여 즉시 출력되도록 설정
  pthread_t t1, t2;  // 두 개의 스레드 ID를 저장할 변수 선언

  // 첫 번째 스레드 생성, 'abc' 함수를 실행
  pthread_create(&t1, NULL, abc, NULL);

  // 두 번째 스레드 생성, 'killABC' 함수를 실행하며 't1'의 주소를 인자로 전달
  pthread_create(&t2, NULL, killABC, (void *)&t1);

  // 생성된 스레드들이 종료될 때까지 메인 스레드가 대기
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;  // 프로그램 종료
}