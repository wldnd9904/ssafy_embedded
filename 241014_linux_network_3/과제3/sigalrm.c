#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <signal.h>     // 시그널 처리를 위한 헤더 파일 (signal, alarm 함수 사용 및 시그널 정의)
#include <stdlib.h>     // 표준 라이브러리 함수 (exit 등)를 사용하기 위한 헤더 파일
#include <unistd.h>     // UNIX 표준 함수 (sleep, alarm 등)를 사용하기 위한 헤더 파일

// SIGALRM 시그널이 발생하면 호출되는 함수
void gogo() {
    printf("WAKE UP!\n");  // 시그널 수신 시 메시지 출력
    exit(1);               // 프로그램 종료 (비정상 종료)
}

int main() {
    // SIGALRM 시그널이 발생하면 gogo 함수를 실행하도록 설정
    signal(SIGALRM, gogo);

    printf("3 seconds\n"); // 알람이 설정되었음을 알리는 메시지 출력
    alarm(3);              // 3초 후에 SIGALRM 시그널을 발생시킴
    printf("wait....\n");  // 대기 중임을 알리는 메시지 출력

    // 무한 루프
    while(1) sleep(1);  // 프로세스가 종료되지 않고 계속 대기이지만, 3초뒤 SIGALRM 발생하여 종료

    return 0;  // 프로그램 정상 종료
}
