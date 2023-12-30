#include <bits/stdc++.h>

constexpr bool is_multitest = false;
constexpr int32_t inf32 = int32_t(1) << 30;
constexpr int64_t inf64 = int64_t(1) << 60;

void solve([[maybe_unused]] int _t) {
  std::vector<std::string> grid;
  std::string s;

  while (!std::cin.eof()) {
    std::cin >> s;
    grid.emplace_back(s);
  }
  grid.pop_back();

  auto expand = [] (const std::vector<std::string> &grid) {
    std::vector<std::string> expanded;

    for (auto &s: grid) {
      expanded.emplace_back(s);
      if (std::all_of(s.begin(), s.end(), [] (char c) { return c == '.'; }))
        expanded.emplace_back(s);
    }

    return expanded;
  };

  auto transpose = [] (const std::vector<std::string> &grid) {
    int n = grid.size(), m = grid.front().size();
    std::vector<std::string> transposed(m, std::string(n, '-'));

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        transposed[j][i] = grid[i][j];
    
    return transposed;
  };

  grid = expand(grid);
  grid = transpose(grid);
  grid = expand(grid);

  int n = grid.size(), m = grid.front().size();
  std::vector<std::pair<int, int>> locations;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (grid[i][j] == '#')
        locations.emplace_back(i, j);
  
  int k = locations.size();
  int64_t ans = 0;
  for (int i = 0; i < k; ++i) {
    for (int j = i + 1; j < k; ++j)
      ans += std::abs(locations[i].first - locations[j].first) + std::abs(locations[i].second - locations[j].second);
  }

  std::cout << "Day 11 (Part 1): " << ans << '\n';
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
