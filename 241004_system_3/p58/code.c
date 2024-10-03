#include <signal.h>  // 시그널 처리를 위한 헤더 파일
#include <stdio.h>  // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <unistd.h>  // UNIX 표준 함수 (pid, sleep 등)를 사용하기 위한 헤더 파일

// 시그널 핸들러 함수 정의, SIGUSR1 시그널을 받으면 실행됨
void run(int num) {
  printf("HO!\n");  // "HO!" 출력
  printf("num: %d\n", num);
}

int main() {
  // SIGUSR1 시그널이 발생하면 run 함수를 호출하도록 설정
  signal(SIGUSR1, run);

  // 현재 프로세스의 PID를 가져와 출력
  pid_t pid = getpid();
  printf("My PID : %d\n", pid);  // 프로세스 ID 출력

  // 무한 루프를 통해 반복적으로 메시지를 출력
  while (1) {
    printf("HAHIHUHEHO!\n");  // "HAHIHUHEHO!" 출력
    sleep(1);                 // 1초 동안 대기
  }

  return 0;  // 프로그램 종료 (실제 도달하지 않음)
}
