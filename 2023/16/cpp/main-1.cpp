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
  grid.pop_back(); // empty line

  using point = std::pair<int, int>;
  
  auto get_dx_dy = [] (char direction) -> point {
    if (direction == 'R')
      return {0, 1};
    if (direction == 'L')
      return {0, -1};
    if (direction == 'U')
      return {-1, 0};
    return {1, 0};
  };

  int n = grid.size(), m = grid.front().size();
  std::set<std::pair<point, char>> visited;
  std::queue<std::pair<point, char>> q;

  q.emplace(point{0, -1}, 'R');

  while (!q.empty()) {
    auto [p, direction] = q.front();
    q.pop();

    // std::cout << p.first << ' ' << p.second << ' ' << direction << '\n';

    auto [dx, dy] = get_dx_dy(direction);
    int nx = p.first + dx, ny = p.second + dy;

    if (nx < 0 or ny < 0 or nx >= n or ny >= m)
      continue;
    
    if (grid[nx][ny] == '.') {
      if (!visited.count({point{nx, ny}, direction})) {
        q.emplace(point{nx, ny}, direction);
        visited.emplace(point{nx, ny}, direction);
      }
    }
    else if (grid[nx][ny] == '\\') {
      if (direction == 'L')
        direction = 'U';
      else if (direction == 'R')
        direction = 'D';
      else if (direction == 'U')
        direction = 'L';
      else
        direction = 'R';
      if (!visited.count({point{nx, ny}, direction})) {
        q.emplace(point{nx, ny}, direction);
        visited.emplace(point{nx, ny}, direction);
      }
    }
    else if (grid[nx][ny] == '/') {
      if (direction == 'L')
        direction = 'D';
      else if (direction == 'R')
        direction = 'U';
      else if (direction == 'U')
        direction = 'R';
      else
        direction = 'L';
      if (!visited.count({point{nx, ny}, direction})) {
        q.emplace(point{nx, ny}, direction);
        visited.emplace(point{nx, ny}, direction);
      }
    }
    else if (grid[nx][ny] == '-') {
      if (direction == 'U' or direction == 'D') {
        if (!visited.count({point{nx, ny}, 'L'})) {
          q.emplace(point{nx, ny}, 'L');
          visited.emplace(point{nx, ny}, 'L');
        }
        if (!visited.count({point{nx, ny}, 'R'})) {
          q.emplace(point{nx, ny}, 'R');
          visited.emplace(point{nx, ny}, 'R');
        }
      }
      else if (!visited.count({point{nx, ny}, direction})) {
        q.emplace(point{nx, ny}, direction);
        visited.emplace(point{nx, ny}, direction);
      }
    }
    else if (grid[nx][ny] == '|') {
      if (direction == 'L' or direction == 'R') {
        if (!visited.count({point{nx, ny}, 'U'})) {
          q.emplace(point{nx, ny}, 'U');
          visited.emplace(point{nx, ny}, 'U');
        }
        if (!visited.count({point{nx, ny}, 'D'})) {
          q.emplace(point{nx, ny}, 'D');
          visited.emplace(point{nx, ny}, 'D');
        }
      }
      else if (!visited.count({point{nx, ny}, direction})) {
        q.emplace(point{nx, ny}, direction);
        visited.emplace(point{nx, ny}, direction);
      }
    }
  }

  std::set<point> unique;
  for (auto &[p, d]: visited)
    unique.insert(p);

  std::cout << "Day 16 (Part 1): " << unique.size();
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
