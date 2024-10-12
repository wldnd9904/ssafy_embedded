#include <stdio.h>          // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <unistd.h>         // UNIX 표준 함수 (close, read, write 등)를 사용하기 위한 헤더 파일
#include <stdlib.h>         // 표준 라이브러리 함수 (exit, atoi 등)를 사용하기 위한 헤더 파일
#include <signal.h>         // 시그널 처리를 위한 헤더 파일
#include <sys/types.h>      // 데이터 타입 (socklen_t 등)을 사용하기 위한 헤더 파일
#include <sys/socket.h>     // 소켓 프로그래밍을 위한 헤더 파일
#include <netinet/in.h>     // 인터넷 프로토콜 관련 구조체 (sockaddr_in 등)를 사용하기 위한 헤더 파일
#include <arpa/inet.h>      // 인터넷 주소 변환 함수를 사용하기 위한 헤더 파일
#include <string.h>         // 문자열 처리 함수를 사용하기 위한 헤더 파일

// 서버의 IP 주소와 포트 번호 상수 선언
const char *SERVER_IP = "127.0.0.1";  
const char *SERVER_PORT = "12345";

int client_sock;  // 클라이언트 소켓 파일 디스크립터

// SIGINT (Ctrl + C) 시그널이 발생했을 때 호출되는 함수
void interrupt(int arg) {
    printf("\nYou typed Ctrl + C\n");           // 시그널 수신 시 메시지 출력
    printf("Bye\n");

    close(client_sock);                         // 클라이언트 소켓 닫기
    exit(1);                                    // 프로그램 비정상 종료
}

int main() {
    // SIGINT 시그널을 수신하면 interrupt 함수를 실행하도록 설정
    signal(SIGINT, interrupt);

    // 클라이언트 소켓 생성
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock == -1) {
        printf("ERROR :: 1_Socket Create Error\n");  	// 소켓 생성 실패 시 오류 메시지 출력
        exit(1);  					                    // 프로그램 비정상 종료
    }

    // 서버 주소 정보 설정
    struct sockaddr_in server_addr = {0};               // 서버 주소 구조체 초기화
    server_addr.sin_family = AF_INET;                   // IPv4 프로토콜 사용
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // 서버 IP 주소 설정
    server_addr.sin_port = htons(atoi(SERVER_PORT));    // 서버 포트 번호 설정 (문자열을 정수로 변환 후 네트워크 바이트 순서로 변환)
    
    socklen_t server_addr_len = sizeof(server_addr);    // 서버 주소 구조체의 크기

    // 서버에 연결 요청
    if (connect(client_sock, (struct sockaddr *)&server_addr, server_addr_len) == -1) {
        printf("ERROR :: 2_Connect Error\n");                                               // 연결 실패 시 오류 메시지 출력
        exit(1);                                                                            // 프로그램 비정상 종료
    }
    
    char buf[100];                                          // 송수신할 데이터 버퍼
    while (1) {
        memset(buf, 0, 100);                                // 버퍼 초기화
        scanf("%s", buf);                                   // 사용자 입력을 받아 버퍼에 저장
        if (!strcmp(buf, "exit")) {                         // 입력이 "exit"이면
            write(client_sock, buf, strlen(buf));           // 서버에 "exit" 메시지 전송
            break;                                          // 반복문 탈출
        }
        write(client_sock, buf, strlen(buf));               // 서버에 입력한 메시지 전송

        memset(buf, 0, 100);                                // 버퍼 초기화
        int len = read(client_sock, buf, 99);               // 서버로부터 응답 수신
        if (len == 0) {                                     // 서버가 연결을 끊은 경우
            printf("INFO :: Server Disconnected\n");        // 연결 종료 메시지 출력
            break;                                          // 반복문 탈출
        }
        printf("%s\n", buf);                                // 서버로부터 수신한 메시지 출력
    }

    close(client_sock);                                     // 클라이언트 소켓 닫기
    return 0;                                               // 프로그램 정상 종료
}
