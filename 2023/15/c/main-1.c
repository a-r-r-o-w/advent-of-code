#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  const int N = 1000000;
  char buffer[N];

  scanf("%s", buffer);
  int n = strlen(buffer);
  int sum = 0, value = 0;

  for (int i = 0; i < n; ++i) {
    if (buffer[i] == ',') {
      // printf("%d\n", value);
      sum += value;
      value = 0;
      continue;
    }
    value = (value + buffer[i]) * 17 % 256;
  }
  sum += value;

  printf("Day 15 (Part 1): %d\n", sum);

  return 0;
}
