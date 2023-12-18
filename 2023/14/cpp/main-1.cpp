#include <iostream>
#include <string>
#include <vector>

constexpr bool is_multitest = false;
constexpr int32_t inf32 = int32_t(1) << 30;
constexpr int64_t inf64 = int64_t(1) << 60;

void solve([[maybe_unused]] int _t) {
  std::string line;
  std::vector<std::string> grid;

  while (not std::cin.eof()) {
    std::getline(std::cin, line);
    if (not line.empty())
      grid.emplace_back(line);
  }

  int n = grid.size(), m = grid.front().size();

  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) {
      if (grid[i][j] != 'O')
        continue;
      int k = i - 1;
      while (k >= 0 and grid[k][j] == '.')
        --k;
      k += 1;
      grid[k][j] = 'O';
      if (k != i)
        grid[i][j] = '.';
    }
  }

  int answer = 0;

  for (int i = 0; i < n; ++i) {
    int count = 0;
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == 'O')
        ++count;
    }
    answer += count * (n - i);
  }

  std::cout << "Day 14 (Part 1): " << answer << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int cases = 1;
  if (is_multitest)
    std::cin >> cases;
  for (int i = 0; i < cases; ++i)
    solve(i);

  return 0;
}
