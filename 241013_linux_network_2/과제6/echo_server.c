#include <stdio.h>          // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <sys/types.h>      // 데이터 타입 (socklen_t 등)을 사용하기 위한 헤더 파일
#include <sys/socket.h>     // 소켓 프로그래밍을 위한 헤더 파일
#include <signal.h>         // 시그널 처리를 위한 헤더 파일
#include <stdlib.h>         // 표준 라이브러리 함수 (exit 등)를 사용하기 위한 헤더 파일
#include <string.h>         // 문자열 처리 함수를 사용하기 위한 헤더 파일
#include <unistd.h>         // UNIX 표준 함수 (close, read, write 등)를 사용하기 위한 헤더 파일
#include <arpa/inet.h>      // 인터넷 주소 변환 함수 및 구조체 사용을 위한 헤더 파일

// 서버의 포트 번호 상수 선언
//const char *PORT = "12345";

int server_sock;  // 서버 소켓 파일 디스크립터
int client_sock;  // 클라이언트 소켓 파일 디스크립터

// SIGINT (Ctrl + C) 시그널이 발생했을 때 호출되는 함수
void interrupt(int arg) {
    printf("\nYou typed Ctrl + C\n");  		// 시그널 수신 시 메시지 출력
    printf("Bye\n");

    close(client_sock);  			// 클라이언트 소켓 닫기
    close(server_sock);  			// 서버 소켓 닫기
    exit(1);             			// 프로그램 비정상 종료
}

// 문자열에서 개행 문자 '\n'을 제거하는 함수
void removeEnterChar(char *buf) {
    int len = strlen(buf); 			// 문자열 길이 계산
    for (int i = len - 1; i >= 0; i--) {  	// 문자열 끝에서부터 탐색
        if (buf[i] == '\n') {  			// 개행 문자를 찾으면
            buf[i] = '\0';  			// 널 문자로 대체하여 제거
            break;
        }
    }
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("usage: ./server [PORT]\n");
		return 0;
	}
	int port = atoi(argv[1]);
	if(!port){
		printf("ERROR :: invalid PORT\n");
		exit(1);
	}

    // SIGINT 시그널을 수신하면 interrupt 함수를 실행하도록 설정
    signal(SIGINT, interrupt);

    // 서버 소켓 생성
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        printf("ERROR :: 1_Socket Create Error\n");  	// 소켓 생성 실패 시 오류 메시지 출력
        exit(1);  					// 프로그램 비정상 종료
    }
    printf("Server On..\n");  				// 서버가 실행되었음을 알리는 메시지 출력

    // 소켓 옵션 설정: 이미 사용 중인 주소라도 재사용 가능하도록 설정
    int optval = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));

    // 서버 주소 정보 설정
    struct sockaddr_in server_addr = {0};            // 서버 주소 구조체 초기화
    server_addr.sin_family = AF_INET;                // IPv4 프로토콜 사용
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 IP로부터의 연결을 허용
    server_addr.sin_port = htons(port);        // 서버 포트 번호 설정 (문자열을 정수로 변환 후 네트워크 바이트 순서로 변환)
    socklen_t server_addr_len = sizeof(server_addr); // 서버 주소 구조체의 크기

    // 소켓과 주소를 바인딩
    if (bind(server_sock, (struct sockaddr *)&server_addr, server_addr_len) == -1) {
        printf("ERROR :: 2_bind Error\n");  						// 바인딩 실패 시 오류 메시지 출력
        exit(1);  									// 프로그램 비정상 종료
    }
    printf("Bind Success\n");  // 바인딩 성공 메시지 출력

    // 클라이언트의 연결 요청을 대기 (백로그 큐 크기: 5)
    if (listen(server_sock, 5) == -1) {
        printf("ERROR :: 3_listen Error");  		// 연결 대기 실패 시 오류 메시지 출력
        exit(1);  					// 프로그램 비정상 종료
    }
    printf("Wait Client...\n");  			// 클라이언트 대기 메시지 출력

    client_sock = 0;  					// 클라이언트 소켓 초기화
    struct sockaddr_in client_addr = {0};  		// 클라이언트 주소 구조체 초기화
    socklen_t client_addr_len = sizeof(client_addr);  	// 클라이언트 주소 구조체의 크기

    // 서버 메인 루프: 클라이언트 연결 요청을 계속해서 수락
    while (1) {
        memset(&client_addr, 0, client_addr_len);  	// 클라이언트 주소 구조체 초기화

        // 클라이언트의 연결 요청을 수락
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sock == -1) {
            printf("ERROR :: 4_accept Error\n");  						// 연결 수락 실패 시 오류 메시지 출력
            break;  										// 루프 탈출
        }
        printf("Client Connect Success!\n");  							// 클라이언트 연결 성공 메시지 출력

        char buf[100];  						// 송수신할 데이터 버퍼
        while (1) {
            memset(buf, 0, 100);  					// 버퍼 초기화

            int len = read(client_sock, buf, 99);  			// 클라이언트로부터 데이터 수신
            removeEnterChar(buf);  					// 수신한 데이터에서 개행 문자 제거

            if (len == 0) {  						// 클라이언트가 연결을 끊은 경우
                printf("INFO :: Disconnect with client... BYE\n");  	// 연결 종료 메시지 출력
                break;  						// 반복문 탈출
            }

            if (!strcmp("exit", buf)) {  				// 클라이언트가 "exit" 명령어를 보낸 경우
                printf("INFO :: Client want close... BYE\n");  		// 클라이언트의 종료 요청 메시지 출력
                break;  						// 반복문 탈출
            }
            write(client_sock, buf, strlen(buf));  			// 클라이언트로부터 받은 메시지를 그대로 에코하여 전송
        }
        close(client_sock);  						// 현재 클라이언트 소켓 닫기
        printf("Client Bye!\n");  					// 클라이언트 종료 메시지 출력
    }
    close(server_sock);  						// 서버 소켓 닫기
    printf("Server off..\n");  						// 서버 종료 메시지 출력 
    return 0;  								// 프로그램 정상 종료
}
