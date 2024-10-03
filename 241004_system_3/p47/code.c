#include <stdio.h>      // 표준 입출력 라이브러리 포함
#include <sys/types.h>  // 시스템 데이터 타입 정의 (pid_t 포함)
#include <unistd.h>  // 유닉스 표준 기능 포함 (fork, getpid 함수 사용을 위해 포함)

int main() {
  // fork() 함수를 호출하여 새로운 프로세스를 생성하고, 자식 프로세스의 PID를
  // 반환
  pid_t child_pid = fork();

  // fork() 함수는 부모 프로세스에서 자식 프로세스의 PID를 반환하고,
  // 자식 프로세스에서는 0을 반환합니다.

  if (child_pid > 0) {  // 이 조건은 부모 프로세스에서만 참이 됩니다.
    // 부모 프로세스가 실행할 코드
    printf("I'm Parent! I'm Busy!!\n");  // 부모 프로세스에서 메시지 출력
    printf("child PID: %d\n", child_pid);
    while (1);  // 무한 루프를 통해 부모 프로세스가 계속 바쁜 상태로 유지됩니다.
  } else if (child_pid == 0) {  // 이 조건은 자식 프로세스에서만 참이 됩니다.
    // 자식 프로세스가 실행할 코드
    printf("HI! I'm baby! ByeBye\n");  // 자식 프로세스에서 메시지 출력
    printf("child PID: %d\n", child_pid);
  }

  return 0;  // 프로그램 종료
}
