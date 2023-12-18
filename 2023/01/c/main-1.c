#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
  const int N = 128;
  char buffer[N];
  int sum = 0;

  while (fgets(buffer, N, stdin) != NULL) {
    int length = strnlen(buffer, N);
    int first = -1, last = -1;
    for (int i = 0; i < length; ++i) {
      if (isdigit(buffer[i])) {
        if (first == -1)
          first = buffer[i] - '0';
        last = buffer[i] - '0';
      }
    }
    int value = first * 10 + last;
    sum += value;
  }

  printf("Day 1 (Part 1): %d\n", sum);

  return 0;
}
