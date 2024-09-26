#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

#include "ssd.h"

#define PIPE_NAME1 \
  TEXT("\\\\.\\pipe\\MyPipe1")  // Ŭ���̾�Ʈ ��û�� �޴�
                                // ������
#define PIPE_NAME2 TEXT("\\\\.\\pipe\\MyPipe2")  // ���� ������ ������ ������
#define BUFFER_SIZE 4096

int main() {
  initialize_ssd();
  HANDLE hPipe1, hPipe2;
  char buffer[BUFFER_SIZE];
  DWORD bytesRead, bytesWritten;

  // Ŭ���̾�Ʈ ��û ó��
  while (1) {
    // Ŭ���̾�Ʈ ��û�� �޴� �б� ���� ���ӵ� ������
    // ����
    hPipe1 =
        CreateNamedPipe(PIPE_NAME1, PIPE_ACCESS_INBOUND,
                        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                        1, BUFFER_SIZE, BUFFER_SIZE, 0, NULL);

    if (hPipe1 == INVALID_HANDLE_VALUE) {
      printf("Failed to create Pipe1. Error: %d\n", GetLastError());
      return 1;
    }

    // ���� ������ ������ ���� ���� ���ӵ� ������ ����
    hPipe2 =
        CreateNamedPipe(PIPE_NAME2, PIPE_ACCESS_OUTBOUND,
                        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                        1, BUFFER_SIZE, BUFFER_SIZE, 0, NULL);

    if (hPipe2 == INVALID_HANDLE_VALUE) {
      printf("Failed to create Pipe2. Error: %d\n", GetLastError());
      CloseHandle(hPipe1);
      return 1;
    }

    printf("Server is waiting for client to connect...\n");
    // Ŭ���̾�Ʈ ���� ���
    ConnectNamedPipe(hPipe1, NULL);
    ConnectNamedPipe(hPipe2, NULL);

    printf("Client connected.\n");
    while (1) {
      // Ŭ���̾�Ʈ�κ��� �޽��� �б�
      if (ReadFile(hPipe1, buffer, BUFFER_SIZE, &bytesRead, NULL) &&
          bytesRead > 0) {
        buffer[bytesRead] = '\0';  // ���ڿ� ����

        printf("Received from client: %s\n", buffer);
        if (strcmp(buffer, "exit") == 0) {
          break;
        }
        control(buffer);

        // ���� �޽��� �ۼ�
        snprintf(buffer, BUFFER_SIZE, "%s", buffer);
        WriteFile(hPipe2, buffer, strlen(buffer), &bytesWritten, NULL);
      }
    }
    // ����
    CloseHandle(hPipe1);
    CloseHandle(hPipe2);
  }

  printf("Server exiting.\n");
  return 0;
}
