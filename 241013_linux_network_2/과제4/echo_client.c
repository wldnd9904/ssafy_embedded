#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const char *SERVER_IP = "127.0.0.1";
const char *SERVER_PORT = "12345";

int client_sock;

void interrupt(int arg) {
  printf("\nYou typed Ctrl + C\n");
  printf("Bye\n");

  close(client_sock);  // CTRL+C 누르면 종료
  exit(1);
}

int main() {
  signal(SIGINT, interrupt);

  client_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (client_sock == -1) {
    printf("ERROR :: 1_Socket Create Error\n");
    exit(1);  // socket()실패 시 종료
  }

  struct sockaddr_in server_addr = {0};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  server_addr.sin_port = htons(atoi(SERVER_PORT));

  socklen_t server_addr_len = sizeof(server_addr);

  if (connect(client_sock, (struct sockaddr *)&server_addr, server_addr_len) ==
      -1) {
    printf("ERROR :: 2_Connect Error\n");
    exit(1);  // connect() 실패 시 종료
  }

  char buf[100];
  while (1) {
    memset(buf, 0, 100);
    scanf("%s", buf);
    if (!strcmp(buf, "exit")) {
      write(client_sock, buf, strlen(buf));
      break;  // exit 입력 시 break 후 종료
    }
    write(client_sock, buf, strlen(buf));

    memset(buf, 0, 100);
    int len = read(client_sock, buf, 99);
    if (len == 0) {
      printf("INFO :: Server Disconnected\n");
      break;  // 서버 종료됐을 때 클라이언트도 종료
    }
    printf("%s\n", buf);
  }

  close(client_sock);
  return 0;
}
