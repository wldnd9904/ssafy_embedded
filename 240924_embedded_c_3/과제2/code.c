#include <stdio.h>
#include <string.h>

void sort(const char** dest, const char** src, size_t from,
          size_t to) {  // [from, to)
  const char* tmp1[8] = {NULL};
  const char* tmp2[8] = {NULL};
  if (to - from == 1) {
    dest[0] = src[from];
    return;
  }
  size_t mid = from + (to - from) / 2;
  sort(tmp1, src, from, mid);
  sort(tmp2, src, mid, to);
  size_t destIdx = 0, tmp1Idx = 0, tmp2Idx = 0;
  while (tmp1[tmp1Idx] || tmp2[tmp2Idx]) {
    if (destIdx) {
      while (tmp1[tmp1Idx] && !strcmp(dest[destIdx - 1], tmp1[tmp1Idx]))
        tmp1Idx++;
      while (tmp2[tmp2Idx] && !strcmp(dest[destIdx - 1], tmp2[tmp2Idx]))
        tmp2Idx++;
    }
    if (!tmp1[tmp1Idx] && !tmp2[tmp2Idx])
      break;
    else if (!tmp1[tmp1Idx])
      dest[destIdx++] = tmp2[tmp2Idx++];
    else if (!tmp2[tmp2Idx])
      dest[destIdx++] = tmp1[tmp1Idx++];
    else if (strcmp(tmp1[tmp1Idx], tmp2[tmp2Idx]) <= 0)
      dest[destIdx++] = tmp1[tmp1Idx++];
    else
      dest[destIdx++] = tmp2[tmp2Idx++];
  }
}

int main() {
  const char* p[7] = {"BTS", "BTS", "BBQ", "BTS", "BBQ", "ABCD", "AS"};
  const char* sorted[8] = {NULL};

  sort(sorted, p, 0, 7);

  size_t idx = 0;
  while (sorted[idx]) printf("%s\n", sorted[idx++]);
  return 0;
}
