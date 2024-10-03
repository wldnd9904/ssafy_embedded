#include <signal.h>  // 시그널 처리를 위한 헤더 파일 (kill 함수 사용 및 시그널 정의)
#include <stdio.h>  // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <stdlib.h>  // 표준 라이브러리 함수 (exit 등)를 사용하기 위한 헤더 파일
#include <sys/types.h>  // 데이터 타입 (pid_t 등)을 사용하기 위한 헤더 파일

int main() {
  // gogo 프로그램을 먼저 실행해서 해당 프로세스의 PID를 확인한 후,
  // 이 값을 target_pid에 설정하고 코드를 빌드해야 함
  pid_t target_pid = 4609;  // 시그널을 보낼 대상 프로세스의 PID 설정 (초기값 0)

  // target_pid가 설정되지 않은 경우 프로그램을 종료
  if (target_pid == 0) {
    printf("Set up Signal Number\n");  // 시그널을 보낼 PID를 설정하지 않았다는
                                       // 메시지 출력
    exit(1);  // 비정상 종료 (에러 코드 1)
  }

  // target_pid에 SIGUSR1 시그널을 전송
  int ret = kill(target_pid, SIGUSR1);

  // 시그널 전송이 성공했는지 확인
  if (ret == 0) {
    printf("%d <- signal transmit!\n",
           target_pid);  // 시그널 전송 성공 시 메시지 출력
  } else {
    printf("Fail!\n");  // 시그널 전송 실패 시 실패 메시지 출력
    exit(1);            // 비정상 종료 (에러 코드 1)
  }

  return 0;  // 프로그램 정상 종료
}
