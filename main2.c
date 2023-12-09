#include <stdio.h>

int main() {
  int cnt = 0;
  for (int i = 0; i < 8 * 1e8; ++i) {
    ++cnt;
  }
  printf("%d", cnt);
  return 0;
}