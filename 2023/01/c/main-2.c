#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
  const int N = 128;
  const char *number_strings[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  char buffer[N];
  int sum = 0;

  while (fgets(buffer, 128, stdin) != NULL) {
    int n = strnlen(buffer, N) - 1;
    buffer[n] = '\0';
    
    int first = -1, last = -1;
    for (int i = 0; i < n; ++i) {
      if (!isdigit(buffer[i])) {
        for (int j = 0; j < 9; ++j) {
          int k = 0;
          while (buffer[i + k] != '\0' && number_strings[j][k] != '\0' && buffer[i + k] == number_strings[j][k])
            ++k;
          if (number_strings[j][k] == '\0') {
            if (first == -1)
              first = j + 1;
            last = j + 1;
          }
        }
      }
      else {
        if (first == -1)
          first = buffer[i] - '0';
        last = buffer[i] - '0';
      }
    }
    printf("%s: %d\n", buffer, first * 10 + last);

    sum += first * 10 + last;
  }

  printf("Day 1 (Part 2): %d\n", sum);

  return 0;
}
