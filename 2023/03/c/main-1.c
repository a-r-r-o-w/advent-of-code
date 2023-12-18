#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
  const int N = 256;
  char grid[N][N];
  int rows = 0, cols = -1;

  while (fgets(grid[rows], N, stdin) != NULL) {
    if (cols == -1)
      cols = strnlen(grid[rows], N) - 1;
    grid[rows][cols] = '\0';
    ++rows;
  }

  const int dx[] = {+1, -1, 0, 0, +1, -1, +1, -1};
  const int dy[] = {0, 0, +1, -1, +1, -1, -1, +1};
  int sum = 0;
  
  for (int i = 0; i < rows; ++i) {
    int value = 0;
    int consider = 0;
    
    for (int j = 0; j < cols; ++j) {
      if (!isdigit(grid[i][j])) {
        if (consider || grid[i][j] != '.')
          sum += value;
        value = 0;
        consider = 0;
        continue;
      }
      
      value = value * 10 + grid[i][j] - '0';;
      
      for (int k = 0; k < 8; ++k) {
        int ni = i + dx[k];
        int nj = j + dy[k];

        if (ni < 0 || nj < 0 || ni >= rows || nj >= cols || grid[ni][nj] == '.' || isdigit(grid[ni][nj]))
          continue;
        
        consider = 1;
      }
    }

    if (consider)
      sum += value;
  }

  printf("Day 3 (Part 1): %d", sum);

  return 0;
}
