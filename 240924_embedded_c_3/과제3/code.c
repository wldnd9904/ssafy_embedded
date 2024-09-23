#include <stdio.h>
#include <string.h>

int main() {
  const char* p[3] = {
      "[000053.163123] MIN CO MIN CO MIN CO",
      "[004351.231231] EMBEDDED EM EM EM",
      "[123456.654321] HO HO HO KKK",
  };
  for (int i = 0; i < 3; i++) {
    double time;
    char message[30];
    char result[40];
    sscanf(p[i], "[%lf] %[^\n]s", &time, message);
    sprintf(result, "%d set : %s", (int)time, message);

    printf("%s\n", result);
  }
  return 0;
}
