#include <algorithm>
#include <bits/stdc++.h>

constexpr bool is_multitest = false;
constexpr int32_t inf32 = int32_t(1) << 30;
constexpr int64_t inf64 = int64_t(1) << 60;

namespace arrow {
  template <typename T>
  concept ostreamable = requires (T x) {
    std::cout << x;
    std::cerr << x;
  };

  template <typename T>
  concept iterable = requires (T x) {
    x.begin();
    x.end();
  };

  class view {
    private:
      std::ostream& stream;
      int depth;
      int space;

    public:
      view (std::ostream& stream = std::cerr, int depth = 0, int space = 2)
        : stream (stream),
          depth  (depth),
          space  (space)
      { }
    
      view& operator () ()
      { return *this; }
  
#ifdef LOST_IN_SPACE
    public:
      template <typename T> requires ostreamable <T>
      view& operator () (const T& object) {
        stream << object;
        return *this;
      }

      template <typename T> requires (iterable <T> and not ostreamable <T>)
      view& operator () (const T& object) {
        operator()("[");
        for (auto element: object)
          operator()(element, ", ");
        operator()(object.begin() == object.end() ? "]" : "\b\b]");
        return *this;
      }

      template <size_t N, typename...T>
      std::enable_if_t <(sizeof...(T) <= N), view&>
      operator () (const std::tuple <T...>&)
      { return *this; }

      template <size_t N, typename... T>
      std::enable_if_t <(sizeof...(T) > N), view&>
      operator () (const std::tuple <T...>& tuple) {
        operator()(std::get <N> (tuple), sizeof...(T) == N + 1 ? "" : ", ");
        operator() <N + 1, T...> (tuple);
        return *this;
      }

      template <typename... T>
      view& operator () (const std::tuple <T...>& tuple) {
        operator()("(");
        operator() <0, T...> (tuple);
        operator()(")");
        return *this;
      }

      template <typename U, typename... V>
      view& operator () (const U& object, const V&... others) {
        static_assert(sizeof...(others) > 0);
        return operator()(object)(others...);
      }

      template <typename U, typename V>
      view& operator () (const std::pair <U, V>& pair) {
        operator()('(', pair.first, ", ", pair.second, ')');
        return *this;
      }

      template <typename T> requires (not iterable <T>)
      view& operator () (const std::vector <T>& vector) {
        operator()("[");

        int index = 0;
        for (auto element: vector) {
          operator()(element, index == int(vector.size()) - 1 ? "" : ", ");
          ++index;
        }

        operator()("]");
        return *this;
      }

      template <typename T> requires iterable <T>
      view& operator () (const std::vector <T>& vector) {
        depth += 1;
        std::string padding (depth * space, ' ');
        operator()("[", !vector.empty() ? "\n" : "");

        int index = 0;
        for (auto element: vector) {
          operator()("  ", padding, "[", index, "]: ", element, index == int(vector.size()) - 1 ? "\n" : ",\n");
          ++index;
        }

        operator()(!vector.empty() ? padding : "", "]");
        depth -= 1;

        return *this;
      }

      template <typename U, typename V>
      view& operator () (const std::map <U, V>& map) {
        depth += 1;
        std::string padding (depth * space, ' ');
        operator()("[", !map.empty() ? "\n" : "");
        
        int index = 0;
        for (auto& [key, value]: map) {
          operator()("  ", padding, "\"", key, "\": ", value, index == int(map.size()) - 1 ? "\n" : ",\n");
          ++index;
        }

        operator()(!map.empty() ? padding : "", "]");
        depth -= 1;

        return *this;
      }
#else
    public:
      template <typename... T>
      view& operator () (const T&...)
      { return *this; }
#endif
  };
}

arrow::view debug;
#define print(x) "{\n  \"", #x, "\": ", x, "\n}"

void solve([[maybe_unused]] int _t) {
  const int D = 1000000;
  
  std::vector<std::string> grid;
  std::string s;

  while (!std::cin.eof()) {
    std::cin >> s;
    grid.emplace_back(s);
  }
  grid.pop_back();

  std::vector<int> empty_rows, empty_cols;
  int n = grid.size(), m = grid.front().size();
  
  for (int i = 0; i < n; ++i) {
    if (std::all_of(grid[i].begin(), grid[i].end(), [] (char c) { return c == '.'; }))
      empty_rows.push_back(i);
  }
  for (int i = 0; i < m; ++i) {
    if (std::all_of(grid.begin(), grid.end(), [&] (auto &s) { return s[i] == '.'; }))
      empty_cols.push_back(i);
  }

  std::vector<std::pair<int, int>> locations;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (grid[i][j] == '#')
        locations.emplace_back(i, j);
  
  // debug(print(empty_rows), '\n');
  // debug(print(empty_cols), '\n');
  
  int size = locations.size();
  int64_t ans = 0;
  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size; ++j) {
      int min_r = std::min(locations[i].first, locations[j].first), max_r = min_r ^ locations[i].first ^ locations[j].first;
      int min_c = std::min(locations[i].second, locations[j].second), max_c = min_c ^ locations[i].second ^ locations[j].second;

      int first_r = -1, second_r = empty_rows.size();
      int first_c = -1, second_c = empty_cols.size();
      
      for (int k = 0; k < (int)empty_rows.size(); ++k) {
        if (first_r == -1 and min_r < empty_rows[k])
          first_r = k;
        if (empty_rows[k] < max_r)
          second_r = k;
      }
      for (int k = 0; k < (int)empty_cols.size(); ++k) {
        if (first_c == -1 and min_c < empty_cols[k])
          first_c = k;
        if (empty_cols[k] < max_c)
          second_c = k;
      }

      int r_diff = second_r - first_r + 1;
      int c_diff = second_c - first_c + 1;
      int actual_r_diff = std::abs(locations[i].first - locations[j].first);
      int actual_c_diff = std::abs(locations[i].second - locations[j].second);
      if (r_diff <= 0 or r_diff > (int)empty_rows.size())
        r_diff = 0;
      if (c_diff <= 0 or c_diff > (int)empty_cols.size())
        c_diff = 0;
      // debug(locations[i], ' ', locations[j], ' ', r_diff, ' ', c_diff, ' ', first_c, ' ', second_c, '\n');

      ans += actual_r_diff + r_diff * (D - 1);
      ans += actual_c_diff + c_diff * (D - 1);
    }
  }

  std::cout << "Day 11 (Part 2): " << ans << '\n';
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
