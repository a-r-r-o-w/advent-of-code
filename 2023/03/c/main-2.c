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
  long long int sum = 0;
  
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (grid[i][j] != '*')
        continue;
      
      long long int top_row_left = 0, top_row_right = 0;
      long long int middle_row_left = 0, middle_row_right = 0;
      long long int bottom_row_left = 0, bottom_row_right = 0;
      int total_count = 0;

      // handle number if in top row
      if (i - 1 >= 0) {
        if (isdigit(grid[i - 1][j])) {
          ++total_count;
          int start = j;
          while (start >= 0 && isdigit(grid[i - 1][start]))
            --start;
          start += 1;
          while (start < cols && isdigit(grid[i - 1][start])) {
            top_row_left = top_row_left * 10 + grid[i - 1][start] - '0';
            ++start;
          }
        }
        else {
          if (j - 1 >= 0 && isdigit(grid[i - 1][j - 1])) {
            ++total_count;
            int start = j - 1, factor = 1;
            while (start >= 0 && isdigit(grid[i - 1][start])) {
              top_row_left += factor * (grid[i - 1][start] - '0');
              factor *= 10;
              --start;
            }
          }
          if (j + 1 < cols && isdigit(grid[i - 1][j + 1])) {
            ++total_count;
            int start = j + 1;
            while (start < cols && isdigit(grid[i - 1][start])) {
              top_row_right = top_row_right * 10 + grid[i - 1][start] - '0';
              ++start;
            }
          }
        }
      }

      // handle middle row
      {
        if (j - 1 >= 0 && isdigit(grid[i][j - 1])) {
          ++total_count;
          int start = j - 1, factor = 1;
          while (start >= 0 && isdigit(grid[i][start])) {
            middle_row_left += factor * (grid[i][start] - '0');
            factor *= 10;
            --start;
          }
        }
        
        if (j + 1 < cols && isdigit(grid[i][j + 1])) {
          ++total_count;
          int start = j + 1;
          while (start < cols && isdigit(grid[i][start])) {
            middle_row_right = middle_row_right * 10 + grid[i][start] - '0';
            ++start;
          }
        }
      }

      // handle number if in bottom row
      if (i + 1 < rows) {
        if (isdigit(grid[i + 1][j])) {
          ++total_count;
          int start = j;
          while (start >= 0 && isdigit(grid[i + 1][start]))
            --start;
          start += 1;
          while (start < cols && isdigit(grid[i + 1][start])) {
            bottom_row_left = bottom_row_left * 10 + grid[i + 1][start] - '0';
            ++start;
          }
        }
        else {
          if (j - 1 >= 0 && isdigit(grid[i + 1][j - 1])) {
            ++total_count;
            int start = j - 1, factor = 1;
            while (start >= 0 && isdigit(grid[i + 1][start])) {
              bottom_row_left += factor * (grid[i + 1][start] - '0');
              factor *= 10;
              --start;
            }
          }
          if (j + 1 < cols && isdigit(grid[i + 1][j + 1])) {
            ++total_count;
            int start = j + 1;
            while (start < cols && isdigit(grid[i + 1][start])) {
              bottom_row_right = bottom_row_right * 10 + grid[i + 1][start] - '0';
              ++start;
            }
          }
        }
      }

      if (total_count != 2)
        continue;
      if (top_row_left == 0) top_row_left = 1;
      if (top_row_right == 0) top_row_right = 1;
      if (middle_row_left == 0) middle_row_left = 1;
      if (middle_row_right == 0) middle_row_right = 1;
      if (bottom_row_left == 0) bottom_row_left = 1;
      if (bottom_row_right == 0) bottom_row_right = 1;

      // printf("%lld %lld %lld %lld %lld %lld\n", top_row_left, top_row_right, middle_row_left, middle_row_right, bottom_row_left, bottom_row_right);
      long long int value = top_row_left * top_row_right * middle_row_left * middle_row_right * bottom_row_left * bottom_row_right;
      sum += value;
    }
  }

  printf("Day 3 (Part 2): %lld", sum);

  return 0;
}
