#include <stdio.h>
#include <windows.h>

#define PIPE_NAME1 TEXT("\\\\.\\pipe\\MyPipe1")  // Ŭ���̾�Ʈ ��û ������
#define PIPE_NAME2 TEXT("\\\\.\\pipe\\MyPipe2")  // ���� ���� ������
#define BUFFER_SIZE 4096

HANDLE hPipe1, hPipe2;
char buffer[BUFFER_SIZE];
DWORD bytesWritten, bytesRead;

int main(int argc, char* argv[]) {
    // Ŭ���̾�Ʈ ��û�� ������ ������ ����
    hPipe1 =
        CreateFile(PIPE_NAME1, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    // ���� ������ �޴� ������ ����
    hPipe2 =
        CreateFile(PIPE_NAME2, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hPipe1 == INVALID_HANDLE_VALUE || hPipe2 == INVALID_HANDLE_VALUE) {
        printf("Failed to connect to pipes. Error: %d\n", GetLastError());
        return 1;
    }
    printf("Connected to SSD.\n");

    if (argc == 1) {  // ���������� ���
        while (1) {
            printf(">> ");
            fgets(buffer, BUFFER_SIZE, stdin);  // �Է�
            buffer[strcspn(buffer, "\n")] = 0;
            WriteFile(hPipe1, buffer, strlen(buffer), &bytesWritten, NULL);  // ��û
            if (ReadFile(hPipe2, buffer, BUFFER_SIZE, &bytesRead, NULL) &&   // ����
                bytesRead > 0) {
                buffer[bytesRead] = '\0';
                printf("%s\n", buffer);  // ���
            }
            if (strcmp(buffer, "exit") == 0) break;
        }
    }
    else {                                         // ��ũ��Ʈ ���
        FILE* file = fopen(argv[1], "r");              // �Է� ����
        FILE* result_file = fopen("result.txt", "w");  // ��� ����

        if (!file || !result_file) {
            perror("���� ���� ����");
        }
        else {
            while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
                buffer[strcspn(buffer, "\n")] = 0;
                if (strcmp(buffer, "exit") == 0) break;  // Ȥ�ó� exit�̸� ����
                WriteFile(hPipe1, buffer, strlen(buffer), &bytesWritten, NULL);
                if (ReadFile(hPipe2, buffer, BUFFER_SIZE, &bytesRead, NULL) &&
                    bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    fprintf(result_file, "%s\n", buffer);
                }
            }
            fclose(file);
            fclose(result_file);
        }
        WriteFile(hPipe1, "exit", 4, &bytesWritten, NULL);  // ���� ����
    }

    // ����
    CloseHandle(hPipe1);
    CloseHandle(hPipe2);
    printf("Client exiting.\n");
    return 0;
}