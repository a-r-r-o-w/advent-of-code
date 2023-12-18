#include <stdio.h>
#include <string.h>

int max(int a, int b) {
  return a > b ? a : b;
}

int main() {
  const int N = 256;
  char buffer[N];
  int sum = 0;

  while (fgets(buffer, N, stdin) != NULL) {
    int n = strnlen(buffer, N) - 1, game_index = 0;
    int red = 0, green = 0, blue = 0;
    buffer[n] = '\0';

    // ignore "Game "
    int i;
    for (i = 5; i < n; ++i) {
      if (buffer[i] == ':')
        break;
      game_index = game_index * 10 + buffer[i] - '0';
    }

    for (char *end_semi, *semi = strtok_r(buffer + i + 1, ";", &end_semi); semi != NULL; semi = strtok_r(NULL, ";", &end_semi)) {
      for (char *end_comma, *comma = strtok_r(semi, ",", &end_comma); comma != NULL; comma = strtok_r(NULL, ",", &end_comma)) {
        char *end_space, *space = strtok_r(comma, " ", &end_space);
        int len = strlen(space), value = 0;
        
        for (int i = 0; i < len; ++i)
          value = value * 10 + space[i] - '0';
        
        space = strtok_r(NULL, " ", &end_space);
        
        if (strncmp(space, "red", 3) == 0)
          red = max(red, value);
        else if (strncmp(space, "blue", 4) == 0)
          blue = max(blue, value);
        else
          green = max(green, value);
      }
    }

    // printf("%d %d %d %d\n", game_index, red, green, blue);
    sum += red * green * blue;
  }

  printf("Day 2 (Part 1): %d\n", sum);

  return 0;
}
