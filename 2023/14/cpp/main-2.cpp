#include <iostream>
#include <map>
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

  auto rotate = [&] (std::vector<std::string> &grid, char direction) {
    if (direction == 'N') {
      for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
          if (grid[i][j] != 'O')
            continue;
          int k = i - 1;
          while (k >= 0 and grid[k][j] == '.')
            --k;
          k += 1;
          grid[i][j] = '.';
          grid[k][j] = 'O';
        }
      }
    }
    if (direction == 'S') {
      for (int j = 0; j < m; ++j) {
        for (int i = n - 1; i >= 0; --i) {
          if (grid[i][j] != 'O')
            continue;
          int k = i + 1;
          while (k < n and grid[k][j] == '.')
            ++k;
          k -= 1;
          grid[i][j] = '.';
          grid[k][j] = 'O';
        }
      }
    }
    if (direction == 'W') {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          if (grid[i][j] != 'O')
            continue;
          int k = j - 1;
          while (k >= 0 and grid[i][k] == '.')
            --k;
          k += 1;
          grid[i][j] = '.';
          grid[i][k] = 'O';
        }
      }
    }
    if (direction == 'E') {
      for (int i = 0; i < n; ++i) {
        for (int j = m - 1; j >= 0; --j) {
          if (grid[i][j] != 'O')
            continue;
          int k = j + 1;
          while (k < m and grid[i][k] == '.')
            ++k;
          k -= 1;
          grid[i][j] = '.';
          grid[i][k] = 'O';
        }
      }
    }
    // std::cout << "Direction: " << direction << '\n';
    // for (int i = 0; i < n; ++i)
    //   std::cout << grid[i] << '\n';
    // std::cout << '\n';
  };

  auto score = [&] (const std::vector<std::string> &grid) {
    int value = 0;
    for (int i = 0; i < n; ++i) {
      int count = 0;
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == 'O')
          ++count;
      }
      value += count * (n - i);
    }
    return value;
  };

  std::map<std::vector<std::string>, std::vector<int>> have;
  const int total = 1'000'000'000;
  int i = 0;
  
  while (i < total) {
    ++i;
    have[grid].push_back(i);
    
    for (char d: {'N', 'W', 'S', 'E'})
      rotate(grid, d);
    
    if ((int)have[grid].size() >= 5) {
      int cycle_length = have[grid][1] - have[grid][0];
      bool okay = true;
      
      for (int j = 2; j < (int)have[grid].size(); ++j) {
        if (cycle_length != have[grid][j] - have[grid][j - 1]) {
          okay = false;
          break;
        }
      }

      if (okay) {
        int times = (total - i) / cycle_length;
        i += times * cycle_length;
      }
    }
  }

  std::cout << "Day 14 (Part 2): " << score(grid) << '\n';
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
