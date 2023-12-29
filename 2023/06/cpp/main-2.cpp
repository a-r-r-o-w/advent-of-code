#include <bits/stdc++.h>
#include <cstdint>
#include <string>

constexpr bool is_multitest = false;
constexpr int32_t inf32 = int32_t(1) << 30;
constexpr int64_t inf64 = int64_t(1) << 60;

void solve([[maybe_unused]] int _t) {
  std::string s;
  std::vector<int64_t> t, d;
  std::stringstream ss;
  
  std::cin >> s;
  std::getline(std::cin, s);
  ss << s;
  while (!ss.eof()) {
    int x; ss >> x;
    t.push_back(x);
  }

  std::cin >> s;
  std::getline(std::cin, s);
  ss.clear();
  ss << s;
  while (!ss.eof()) {
    int x; ss >> x;
    d.push_back(x);
  }

  std::string time, distance;
  for (int x: t)
    time += std::to_string(x);
  for (int x: d)
    distance += std::to_string(x);
  
  int64_t tt = std::stoll(time);
  int64_t dd = std::stoll(distance);
  t.clear(); t.push_back(tt);
  d.clear(); d.push_back(dd);

  int n = t.size();
  int64_t ans = 1;

  for (int i = 0; i < n; ++i) {
    int T = t[i] / 2;
    if (T * (t[i] - T) < d[i])
      continue;
    
    int low_left = 0, high_left = T;
    while (low_left < high_left) {
      int mid = (low_left + high_left) / 2;
      if (mid * (t[i] - mid) <= d[i])
        low_left = mid + 1;
      else
        high_left = mid;
    }

    int low_right = T, high_right = t[i] + 1;
    while (low_right < high_right) {
      int mid = (low_right + high_right) / 2;
      if (mid * (t[i] - mid) > d[i])
        low_right = mid + 1;
      else
        high_right = mid;
    }

    // for (int j = low_left; j < low_right; ++j)
    //   std::cout << j * (t[i] - j) << ' ';
    // std::cout << '\n';

    int64_t have = low_right - low_left;
    // std::cout << i << ' ' << have << '\n';
    ans *= have;
  }

  std::cout << "Day 6 (Part 2): " << ans << '\n';
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
