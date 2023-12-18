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
  std::vector<int> dx = {+1, -1, 0, 0};
  std::vector<int> dy = {0, 0, +1, -1};
  char index_to_direction[] = {'D', 'U', 'R', 'L'};
  std::unordered_map<char, char> opposite_direction = {
    {'D', 'U'},
    {'U', 'D'},
    {'R', 'L'},
    {'L', 'R'},
  };
  std::unordered_map<char, int> direction_to_index = {
    {'D', 0},
    {'U', 1},
    {'R', 2},
    {'L', 3},
  };
  std::vector<std::string> grid;
  std::string s;

  while (!std::cin.eof()) {
    std::cin >> s;
    grid.emplace_back(s);
  }
  grid.pop_back(); // remove empty line

  int n = grid.size(), m = grid.front().size();
  std::priority_queue<std::tuple<int, int, int, int, int>> pq;
  std::map<std::tuple<int, int, int, char>, int> have;

  pq.emplace(0, 0, 0, -1, -1);

  while (!pq.empty()) {
    auto [cost, r, c, direction, count] = pq.top();
    debug(pq.top(), '\n');
    pq.pop();
    
    for (int i = 0; i < 4; ++i) {
      int dr = r + dx[i], dc = c + dy[i];
      int new_count = i == direction ? count + 1 : 1;
      if (dr >= 0 and dr < n and dc >= 0 and dc < m and new_count <= 10 and !have.count({dr, dc, i, new_count}) and (direction == -1 or index_to_direction[i] != opposite_direction[index_to_direction[direction]]) and (count == -1 or i == direction or count >= 4)) {
        int d = grid[dr][dc] - '0';
        pq.emplace(cost - d, dr, dc, i, new_count);
        have[{dr, dc, i, new_count}] = d - cost;
      }
    }
  }

  int ans = inf32;
  for (auto &[key, value]: have) {
    auto &[r, c, direction, count] = key;
    if (r == n - 1 and c == m - 1)
      ans = std::min(ans, value);
  }
  
  std::cout << "Day 17 (Part 1): " << ans << '\n';
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
