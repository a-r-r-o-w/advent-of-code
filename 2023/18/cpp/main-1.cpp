#include <bits/stdc++.h>
#include <cstdint>

constexpr bool is_multitest = false;
constexpr int32_t inf32 = int32_t(1) << 30;
constexpr int64_t inf64 = int64_t(1) << 60;

void solve([[maybe_unused]] int _t) {
  std::vector<std::tuple<char, int, std::string>> instructions;

  auto read = [] (auto &x) {
    std::cin >> x;
    return !std::cin.eof();
  };

  char c; int x; std::string s;
  while (read(c) and read(x) and read(s))
    instructions.emplace_back(c, x, s);

  int edge_cells = 0;
  std::vector<std::pair<int64_t, int64_t>> vertices;
  int64_t cx = 0, cy = 0;

  for (auto &[c, steps, s]: instructions) {
    int dx = c == 'U' ? -1 : c == 'D' ? +1 : 0;
    int dy = c == 'L' ? -1 : c == 'R' ? +1 : 0;
    cx += steps * dx;
    cy += steps * dy;
    edge_cells += steps;
    vertices.emplace_back(cx, cy);
  }

  auto shoelace_area = [] (const std::vector<std::pair<int64_t, int64_t>> &points) {
    int k = points.size();
    int64_t area = 0;
    for (int i = 0; i < k; ++i)
      area += points[i].first * points[(i + 1) % k].second - points[(i + 1) % k].first * points[i].second;
    return std::abs(area);
  };

  int64_t A = shoelace_area(vertices);
  int64_t ans = (A - edge_cells) / 2 + 1 + edge_cells;
  
  std::cout << "Day 18 (Part 1): " << ans << '\n';
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
