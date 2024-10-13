#include <stdio.h>             // 표준 입출력 함수
#include <unistd.h>            // 유닉스 표준 함수 정의
#include <stdlib.h>            // 표준 라이브러리 함수
#include <signal.h>            // 신호 처리 함수
#include <sys/types.h>         // 시스템 호출에 사용되는 데이터 타입
#include <sys/socket.h>        // 소켓 함수와 데이터 구조체
#include <netinet/in.h>        // 인터넷 주소 체계 (sockaddr_in)
#include <arpa/inet.h>         // 인터넷 작업 관련 함수 (inet_addr 등)
#include <string.h>            // 문자열 처리 함수
#include <pthread.h>           // POSIX 스레드 라이브러리

#define NAME_SIZE 20           // 사용자 이름의 최대 크기
#define MSG_SIZE 100           // 메시지의 최대 크기

char name[NAME_SIZE];          // 사용자 이름을 저장할 전역 변수
char msg[MSG_SIZE];            // 메시지를 저장할 전역 변수

pthread_t send_tid;            // 메시지를 보내는 스레드의 ID
pthread_t receive_tid;         // 메시지를 받는 스레드의 ID
int exitFlag;                  // 프로그램 종료를 위한 플래그

char SERVER_IP[20];            // 서버 IP 주소를 저장할 전역 변수
char SERVER_PORT[6];           // 서버 포트 번호를 저장할 전역 변수

int client_sock;               // 클라이언트 소켓 디스크립터

// Ctrl + C 신호를 처리하는 함수
void interrupt(int arg){
    printf("\nYou typped Ctrl + C\n");
    printf("Bye\n");

    // 스레드를 취소하고 종료를 기다림
    pthread_cancel(send_tid);
    pthread_cancel(receive_tid);

    pthread_join(send_tid, 0);
    pthread_join(receive_tid, 0);

    // 소켓을 닫고 프로그램을 종료
    close(client_sock);
    exit(1);
}

// 메시지를 서버로 보내는 스레드 함수
void *sendMsg(){
    char buf[NAME_SIZE + MSG_SIZE + 1];  // 전송할 메시지를 저장할 버퍼

    while (!exitFlag){
        memset(buf, 0, NAME_SIZE + MSG_SIZE);  // 버퍼를 초기화
        
        fgets(msg, MSG_SIZE, stdin);  // 표준 입력으로부터 메시지를 입력받음
        if (!strcmp(msg, "exit\n")){  // 'exit' 입력 시 종료 플래그 설정
            exitFlag = 1;
            write(client_sock, msg, strlen(msg));  // 서버로 'exit' 메시지 전송
            break;
        }
        if (exitFlag) break;
        sprintf(buf, "%s %s", name, msg);  // 이름과 메시지를 합쳐 버퍼에 저장
        write(client_sock, buf, strlen(buf));  // 서버로 메시지 전송
    }
}

// 서버로부터 메시지를 받는 스레드 함수
void *receiveMsg(){
    char buf[NAME_SIZE + MSG_SIZE];  // 수신할 메시지를 저장할 버퍼
    while (!exitFlag){
        memset(buf, 0, NAME_SIZE + MSG_SIZE);  // 버퍼를 초기화
        int len = read(client_sock, buf, NAME_SIZE + MSG_SIZE - 1);  // 서버로부터 메시지 수신
        if (len == 0){  // 서버가 연결을 끊었을 경우
            printf("INFO :: Server Disconnected\n");
            kill(0, SIGINT);  // SIGINT 신호를 보내 프로그램을 종료
            exitFlag = 1;
            break;
        }
        printf("%s\n", buf);  // 수신한 메시지를 출력
    }
}

int main(int argc, char *argv[]){
    if( argc<4 ){
        printf("ERROR Input [IP Addr] [Port Num] [User Name]\n");
        exit(1);
    }
    strcpy(SERVER_IP, argv[1]);  // 서버 IP 주소 저장
    strcpy(SERVER_PORT, argv[2]);  // 서버 포트 번호 저장
    sprintf(name, "[%s]", argv[3]);  // 사용자 이름 저장

    signal(SIGINT, interrupt);  // SIGINT 신호를 처리할 함수 설정
    
    client_sock = socket(AF_INET, SOCK_STREAM, 0);  // TCP 소켓 생성
    if (client_sock == -1){
        printf("ERROR :: 1_Socket Create Error\n");
        exit(1);
    }
    //printf("Socket Create!\n");
    
    struct sockaddr_in server_addr = {0};  // 서버 주소 구조체 초기화
    server_addr.sin_family = AF_INET;  // 주소 체계를 IPv4로 설정
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  // 서버 IP 주소 설정
    server_addr.sin_port = htons(atoi(SERVER_PORT));  // 서버 포트 번호 설정
    socklen_t server_addr_len = sizeof(server_addr);
    
    // 서버에 연결 시도
    if (connect(client_sock, (struct sockaddr *)&server_addr, server_addr_len) == -1){
        printf("ERROR :: 2_Connect Error\n");
        exit(1);
    }
    //printf("Connect Success!\n");
    
    // 메시지를 보내고 받는 스레드 생성
    pthread_create(&send_tid, NULL, sendMsg, NULL);
    pthread_create(&receive_tid, NULL, receiveMsg, NULL);

    // 스레드가 종료될 때까지 대기
    pthread_join(send_tid, 0);
    pthread_join(receive_tid, 0);

    // 소켓을 닫고 프로그램 종료
    close(client_sock);
    return 0;
}
