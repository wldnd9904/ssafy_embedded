#include <stdio.h>
#include <windows.h>

#define PIPE_NAME1 TEXT("\\\\.\\pipe\\MyPipe1")  // 클라이언트 요청 파이프
#define PIPE_NAME2 TEXT("\\\\.\\pipe\\MyPipe2")  // 서버 응답 파이프
#define BUFFER_SIZE 4096

HANDLE hPipe1, hPipe2;
char buffer[BUFFER_SIZE];
DWORD bytesWritten, bytesRead;

int main(int argc, char* argv[]) {
    // 클라이언트 요청을 보내는 파이프 연결
    hPipe1 =
        CreateFile(PIPE_NAME1, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    // 서버 응답을 받는 파이프 연결
    hPipe2 =
        CreateFile(PIPE_NAME2, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hPipe1 == INVALID_HANDLE_VALUE || hPipe2 == INVALID_HANDLE_VALUE) {
        printf("Failed to connect to pipes. Error: %d\n", GetLastError());
        return 1;
    }
    printf("Connected to SSD.\n");

    if (argc == 1) {  // 인터프리터 모드
        while (1) {
            printf(">> ");
            fgets(buffer, BUFFER_SIZE, stdin);  // 입력
            buffer[strcspn(buffer, "\n")] = 0;
            WriteFile(hPipe1, buffer, strlen(buffer), &bytesWritten, NULL);  // 요청
            if (ReadFile(hPipe2, buffer, BUFFER_SIZE, &bytesRead, NULL) &&   // 응답
                bytesRead > 0) {
                buffer[bytesRead] = '\0';
                printf("%s\n", buffer);  // 출력
            }
            if (strcmp(buffer, "exit") == 0) break;
        }
    }
    else {                                         // 스크립트 모드
        FILE* file = fopen(argv[1], "r");              // 입력 파일
        FILE* result_file = fopen("result.txt", "w");  // 출력 파일

        if (!file || !result_file) {
            perror("파일 열기 실패");
        }
        else {
            while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
                buffer[strcspn(buffer, "\n")] = 0;
                if (strcmp(buffer, "exit") == 0) break;  // 혹시나 exit이면 종료
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
        WriteFile(hPipe1, "exit", 4, &bytesWritten, NULL);  // 연결 종료
    }

    // 정리
    CloseHandle(hPipe1);
    CloseHandle(hPipe2);
    printf("Client exiting.\n");
    return 0;
}