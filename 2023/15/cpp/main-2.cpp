#include <algorithm>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <utility>

constexpr bool is_multitest = false;
constexpr int32_t inf32 = int32_t(1) << 30;
constexpr int64_t inf64 = int64_t(1) << 60;

void solve([[maybe_unused]] int _t) {
  std::string s;
  std::cin >> s;
  s += ",";
  int n = s.length();

  int64_t answer = 0, value = 0;
  std::string label;
  int power;
  char symbol;
  std::vector<std::map<std::string, std::pair<int, int>>> v(256);

  for (int i = 0; i < n; ++i) {
    if (s[i] == '=' or s[i] == '-')
      symbol = s[i];
    else if (s[i] >= '0' and s[i] <= '9')
      power = s[i] - '0';
    else if (s[i] == ',') {
      if (symbol == '=') {
        if (v[value].count(label))
          v[value][label].first = power;
        else
          v[value][label] = {power, i};
      }
      else {
        v[value].erase(label);
      }
      value = 0;
      label.clear();
    }
    else {
      value = (value + s[i]) * 17 % 256;
      label += s[i];
    }
  }

  std::vector<std::pair<int, int>> ordered;

  for (int i = 0; i < 256; ++i) {
    int64_t current_answer = 0;
    for (auto &[key, value]: v[i])
      ordered.push_back(value);
    std::sort(ordered.begin(), ordered.end(), [] (auto &l, auto &r) { return l.second < r.second; });
    for (int j = 0; j < (int)ordered.size(); ++j)
      current_answer += int64_t(j + 1) * ordered[j].first;
    answer += (i + 1) * current_answer;
    ordered.clear();
  }

  std::cout << "Day 15 (Part 2): " << answer << '\n';
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
