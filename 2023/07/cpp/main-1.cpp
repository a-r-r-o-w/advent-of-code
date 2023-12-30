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
  std::string deck = "AKQJT98765432";
  int strength[256] = {0};

  for (int index = 0; int c: deck)
    strength[c] = index++;
  
  std::map<char, int> m;
  std::vector<int> v;

  auto kind = [&] (const std::string &s) {
    for (char c: s)
      ++m[c];
    for (auto &[_, x]: m)
      v.push_back(x);
    std::sort(v.begin(), v.end());

    // five of a kind
    if (v == std::vector<int>{5}) return 0;
    // four of a kind
    if (v == std::vector<int>{1, 4}) return 1;
    // full house
    if (v == std::vector<int>{2, 3}) return 2;
    // three of a kind
    if (v == std::vector<int>{1, 1, 3}) return 3;
    // two pair
    if (v == std::vector<int>{1, 2, 2}) return 4;
    // one pair
    if (v == std::vector<int>{1, 1, 1, 2}) return 5;
    // high card
    return 6;
  };

  std::vector<std::tuple<int, std::string, int>> have;
  while (!std::cin.eof()) {
    std::string s; int x;
    std::cin >> s >> x;
    have.emplace_back(kind(s), s, x);
    m.clear();
    v.clear();
  }
  have.pop_back();
  std::sort(have.begin(), have.end(), [&] (auto &l, auto &r) {
    auto &[lk, ls, lx] = l;
    auto &[rk, rs, rx] = r;
    if (lk < rk) return true;
    if (lk > rk) return false;
    for (int i = 0; i < 5; ++i)
      if (strength[(int)ls[i]] < strength[(int)rs[i]]) return true;
      else if (strength[(int)ls[i]] > strength[(int)rs[i]]) return false;
    return false;
  });
  debug(print(have), '\n');

  int n = have.size();
  int64_t ans = 0;

  for (int i = 0; i < n; ++i)
    ans += int64_t(n - i) * std::get<2>(have[i]);
  
  std::cout << "Day 7 (Part 1): " << ans << '\n';
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
