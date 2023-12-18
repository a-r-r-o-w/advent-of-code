#include <cstdint>
#include <iostream>
#include <vector>

constexpr bool is_multitest = false;
constexpr int32_t inf32 = int32_t(1) << 30;
constexpr int64_t inf64 = int64_t(1) << 60;

void solve([[maybe_unused]] int _t) {
  std::string line;
  std::vector<std::string> grid;

  auto convert_grid = [] (const std::vector<std::string> &grid) {
    std::vector<int> values;
    for (int i = 0; i < (int)grid.size(); ++i) {
      int value = 0;
      for (int j = 0; j < (int)grid[i].size(); ++j) {
        if (grid[i][j] == '#')
          value |= 1 << j;
      }
      values.push_back(value);
    }
    return values;
  };

  auto transpose = [] (const std::vector<std::string> &grid) {
    std::vector<std::string> t;
    for (int j = 0; j < (int)grid.front().size(); ++j) {
      std::string s;
      for (int i = 0; i < (int)grid.size(); ++i)
        s += grid[i][j];
      t.emplace_back(std::move(s));
    }
    return t;
  };

  auto process = [] (std::vector<int> &v) {
    int n = v.size(), count = 0;
    
    for (int i = 0; i < n - 1; ++i) {
      int left = i, right = i + 1;
      bool mirror = true;

      while (left >= 0 and right < n) {
        if (v[left] != v[right]) {
          mirror = false;
          break;
        }
        --left;
        ++right;
      }

      if (mirror)
        count += i + 1;
    }

    return count;
  };

  int64_t answer = 0;
  
  while (true) {
    std::getline(std::cin, line);
    if (line.empty()) {
      // process grid
      auto grid_transpose = transpose(grid);
      auto rows = convert_grid(grid);
      auto cols = convert_grid(grid_transpose);

      answer += process(cols);
      answer += 100 * process(rows);

      grid.clear();

      if (std::cin.eof())
        break;
    }
    else
      grid.emplace_back(line);
  }

  std::cout << "Day 13 (Part 1): " << answer << '\n';
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
