#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>

constexpr bool is_multitest = false;
constexpr int32_t inf32 = int32_t(1) << 30;
constexpr int64_t inf64 = int64_t(1) << 60;

void solve([[maybe_unused]] int _t) {
  std::vector<std::vector<int>> v;
  std::string s;
  std::stringstream ss;

  while (!std::cin.eof()) {
    v.push_back({});
    std::getline(std::cin, s);
    ss.clear();
    ss << s;
    while (!ss.eof()) {
      int x;
      ss >> x;
      v.back().emplace_back(x);
    }
  }
  v.pop_back();

  auto find = [&] (auto self, std::vector<int> &x) -> int64_t {
    if (x.empty() or std::all_of(x.begin(), x.end(), [] (int k) { return k == 0; }))
      return 0;
    
    int n = x.size();
    int64_t last = x.back();
    
    for (int i = 0; i < n - 1; ++i)
      x[i] = x[i + 1] - x[i];
    x.pop_back();
    
    return last + self(self, x);
  };

  int64_t ans = 0;
  for (auto &s: v) {
    std::reverse(s.begin(), s.end());
    int64_t value = find(find, s);
    // std::cout << value << ' ';
    ans += value;
  }
  // std::cout << '\n';
  
  std::cout << "Day 9 (Part 2): " << ans << '\n';
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
