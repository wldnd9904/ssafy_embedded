#include <stdio.h>             // 표준 입출력 함수
#include <signal.h>            // 신호 처리 함수
#include <unistd.h>            // 유닉스 표준 함수 정의
#include <stdlib.h>            // 표준 라이브러리 함수
#include <sys/types.h>         // 시스템 호출에 사용되는 데이터 타입
#include <sys/socket.h>        // 소켓 함수와 데이터 구조체
#include <arpa/inet.h>         // 인터넷 작업 관련 함수 (inet_addr 등)
#include <string.h>            // 문자열 처리 함수
#include <pthread.h>           // POSIX 스레드 라이브러리

#define MAX_CLIENT_CNT 500     // 최대 클라이언트 수

char PORT[6];                  // 서버 포트 번호를 저장할 전역 변수
int server_sock;               // 서버 소켓 디스크립터
int client_sock[MAX_CLIENT_CNT] = {0};  // 클라이언트 소켓 디스크립터 배열
struct sockaddr_in client_addr[MAX_CLIENT_CNT] = {0};  // 클라이언트 주소 구조체 배열

pthread_t tid[MAX_CLIENT_CNT]; // 클라이언트별 스레드 ID 배열
int exitFlag[MAX_CLIENT_CNT];  // 클라이언트별 종료 플래그 배열

pthread_mutex_t mlock;         // 임계 구역 보호를 위한 뮤텍스

// Ctrl + C 신호를 처리하는 함수
void interrupt(int arg){
    printf("\nYou typed Ctrl + C\n");
    printf("Bye\n");

    // 모든 클라이언트의 연결을 종료하고 스레드를 정리
    for (int i = 0; i < MAX_CLIENT_CNT; i++){
        if (client_sock[i] != 0){
            pthread_cancel(tid[i]);
            pthread_join(tid[i], 0);
            close(client_sock[i]);
        }
    }
    close(server_sock);  // 서버 소켓을 닫음
    exit(1);
}

// 문자열에서 '\n' 문자를 제거하는 함수
void removeEnterChar(char *buf){
    int len = strlen(buf);
    for (int i = len - 1; i >= 0; i--) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
}

// 사용할 수 있는 클라이언트 ID를 반환하는 함수
int getClientID(){
    for (int i = 0; i < MAX_CLIENT_CNT; i++){
        if (client_sock[i] == 0)
            return i;
    }
    return -1;  // 사용 가능한 ID가 없을 경우 -1 반환
}

// 각 클라이언트를 처리하는 스레드 함수
void *client_handler(void *arg){
    int id = *(int *)arg;  // 클라이언트 ID를 받아옴

    char client_IP[100];  // 클라이언트 IP 주소를 저장할 변수
    strcpy(client_IP, inet_ntoa(client_addr[id].sin_addr));  // 클라이언트 IP 주소 복사
    printf("INFO :: Connect new Client (ID : %d, IP : %s)\n", id, client_IP);

    char buf[MAX_CLIENT_CNT]= { 0 };  // 메시지를 저장할 버퍼
    while (1) {
        memset(buf, 0, MAX_CLIENT_CNT);  // 버퍼 초기화
        int len = read(client_sock[id], buf, MAX_CLIENT_CNT);  // 클라이언트로부터 메시지 읽기
        if (len == 0) {  // 클라이언트가 연결을 끊었을 경우
            printf("INFO :: Disconnect with client.. BYE\n");
            exitFlag[id] = 1;  // 종료 플래그 설정
            break;
        }

        if (!strcmp("exit", buf)) {  // 클라이언트가 'exit' 메시지를 보낸 경우
            printf("INFO :: Client want close.. BYE\n");
            exitFlag[id] = 1;  // 종료 플래그 설정
            break;
        }

        removeEnterChar(buf);  // 메시지에서 '\n' 문자 제거
        pthread_mutex_lock(&mlock);  // 뮤텍스 잠금

        // 모든 클라이언트에게 메시지를 브로드캐스트
        for (int i = 0; i < MAX_CLIENT_CNT; i++){
            if (client_sock[i] != 0){
                write(client_sock[i], buf, strlen(buf));
            }
        }
        pthread_mutex_unlock(&mlock);  // 뮤텍스 해제
    }
    close(client_sock[id]);  // 클라이언트 소켓 닫기
}

int main(int argc, char* argv[]){
    if( argc<2 ){
        printf("ERROR Input Port Num\n");
        exit(1);
    }
    strcpy(PORT, argv[1]);  // 입력된 포트 번호 저장

    signal(SIGINT, interrupt);  // SIGINT 신호를 처리할 함수 설정
    pthread_mutex_init(&mlock, NULL);  // 뮤텍스 초기화

    server_sock = socket(AF_INET, SOCK_STREAM, 0);  // TCP 소켓 생성
    if (server_sock == -1){
        printf("ERROR :: 1_Socket Create Error\n");
        exit(1);
    }    
    printf("Server On..\n");    

    int optval = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));  // 소켓 옵션 설정

    struct sockaddr_in server_addr = {0};  // 서버 주소 구조체 초기화
    server_addr.sin_family = AF_INET;  // 주소 체계를 IPv4로 설정
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 인터페이스에서 연결 허용
    server_addr.sin_port = htons(atoi(PORT));  // 포트 번호 설정

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        printf("ERROR :: 2_bind Error\n");
        exit(1);
    }
    printf("Bind Success\n");
    
    if (listen(server_sock, 5) == -1){  // 연결 대기열 설정
        printf("ERROR :: 3_listen Error");
        exit(1);
    }
    printf("Wait Client...\n");

    socklen_t client_addr_len = sizeof(struct sockaddr_in);
    int id_table[MAX_CLIENT_CNT];  // 클라이언트 ID 테이블

    while (1){
        int id = getClientID();  // 사용 가능한 클라이언트 ID 가져오기
        id_table[id] = id;

        if (id == -1){
            printf("WARNING :: Client FULL\n");  // 최대 클라이언트 수 초과
            sleep(1);
            continue;
        }

        memset(&client_addr[id], 0, sizeof(struct sockaddr_in));  // 클라이언트 주소 초기화

        // 클라이언트 연결 수락
        client_sock[id] = accept(server_sock, (struct sockaddr *)&client_addr[id], &client_addr_len);
        if (client_sock[id] == -1){
            printf("ERROR :: 4_accept Error\n");
            break;
        }

        // 클라이언트를 처리할 스레드 생성
        pthread_create(&tid[id], NULL, client_handler, (void *)&id_table[id]);

        // 종료된 클라이언트 스레드 정리
        for (int i = 0; i < MAX_CLIENT_CNT; i++){
            if (exitFlag[i] == 1){
                exitFlag[i] = 0;
                pthread_join(tid[i], 0);
                client_sock[i] = 0;
            }
        }
    }
    pthread_mutex_destroy(&mlock);  // 뮤텍스 제거
    close(server_sock);  // 서버 소켓 닫기
    return 0;
}
