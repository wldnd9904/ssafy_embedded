#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const char *PORT = "12345";

int server_sock;
int client_sock;

void interrupt(int arg) {
  printf("\nYou typed Ctrl + C\n");
  printf("Bye\n");

  close(client_sock);
  close(server_sock);  // Ctrl+C 누를 경우 서버 소켓 종료
  exit(1);
}

void removeEnterChar(char *buf) {
  int len = strlen(buf);
  for (int i = len - 1; i >= 0; i--) {
    if (buf[i] == '\n') {
      buf[i] = '\0';
      break;
    }
  }
}

int main() {
  signal(SIGINT, interrupt);  // Ctrl+C 누를 경우 서버 소켓 종료

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock == -1) {
    printf("ERROR :: 1_Socket Create Error\n");
    exit(1);  // 유효한 소켓 디스크립터가 없기 때문에 close 필요 없음, 종료
  }
  printf("Server On..\n");

  int optval = 1;
  setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval,
             sizeof(optval));

  struct sockaddr_in server_addr = {0};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi(PORT));
  socklen_t server_addr_len = sizeof(server_addr);

  if (bind(server_sock, (struct sockaddr *)&server_addr, server_addr_len) ==
      -1) {
    printf("ERROR :: 2_bind Error\n");
    exit(1);  // bind()실패 시 소켓 종료 및 프로그램 종료
  }
  printf("Bind Success\n");

  if (listen(server_sock, 5) == -1) {
    printf("ERROR :: 3_listen Error");
    exit(1);  // listen()실패 시 소켓 종료 및 프로그램 종료
  }
  printf("Wait Client...\n");

  client_sock = 0;
  struct sockaddr_in client_addr = {0};
  socklen_t client_addr_len = sizeof(client_addr);

  while (1) {
    memset(&client_addr, 0, client_addr_len);

    client_sock =
        accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sock == -1) {
      printf("ERROR :: 4_accept Error\n");
      break;  // accept() 실패 시 break -> while문 밖에서 서버 소켓 종료
    }
    printf("Client Connect Success!\n");

    char buf[100];
    while (1) {
      memset(buf, 0, 100);

      int len = read(client_sock, buf, 99);
      removeEnterChar(buf);

      if (len == 0) {
        printf("INFO :: Disconnect with client... BYE\n");
        break;
      }

      if (!strcmp("exit", buf)) {
        printf("INFO :: Client want close... BYE\n");
        break;
      }
      write(client_sock, buf, strlen(buf));
    }
    close(client_sock);
    printf("Client Bye!\n");
  }
  close(server_sock);  // 서버 소켓 종료 코드
  printf("Server off..\n");
  return 0;
}
