#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
#include <iostream>
#include <vector>
using namespace atcoder;
using ll = long long;
using ld = long double;
using Graph = vector<vector<int>>;
using vi = vector<int>;
using vl = vector<long>;
using vll = vector<long long>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vvb = vector<vb>;
using vvvb = vector<vvb>;
using vvll = vector<vll>;
using vvvll = vector<vvll>;
using vd = vector<double>;
using vvd = vector<vd>;
using vvvd = vector<vvd>;
using vc = vector<char>;
using vvc = vector<vc>;
using lll = __int128_t;
using vs = vector<string>;
using pii = pair<long long, long long>;
using mint = modint1000000007;
const long double EPS = 1e-10;
const double INF = 1e18;

const long double PI = acos(-1.0L);
#define mp make_pair
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); i++)
#define rep(i, n) for (ll i = (0); i < (ll)(n); i++)
#define rrep(i, n) for (ll i = (1); i < (ll)(n + 1); i++)
#define repd(i, n) for (ll i = n - 1; i >= 0; i--)
#define rrepd(i, n) for (ll i = n; i >= 1; i--)
#define ALL(n) n.begin(), n.end()
#define rALL(n) n.rbegin(), n.rend()
#define fore(i, a) for (auto &i : a)
#define IN(a, x, b) (a <= x && x < b)
#define IN(a, x, b) (a <= x && x < b)
#define INIT                        \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0);
template <class T>
inline T CHMAX(T &a, const T b) {
  return a = (a < b) ? b : a;
}
template <class T>
inline T CHMIN(T &a, const T b) {
  return a = (a > b) ? b : a;
}
#include <algorithm>  // min, max, swap, sort, reverse, lower_bound, upper_bound
#include <bitset>     // bitset
#include <cctype>     // isupper, islower, isdigit, toupper, tolower
#include <cstdint>    // int64_t, int*_t
#include <cstdio>     // printf
#include <deque>      // deque
#include <iostream>   // cout, endl, cin
#include <map>        // map
#include <queue>      // queue, priority_queue
#include <set>        // set
#include <stack>      // stack
#include <string>     // string, to_string, stoi
#include <tuple>      // tuple, make_tuple
#include <unordered_map>  // unordered_map
#include <unordered_set>  // unordered_set
#include <utility>        // pair, make_pair
#include <vector>         // vector
using namespace std;vll EulerianTrail(const int s, vvll &g,
                          const bool directed) {
  function<void(int, vll &)> dfs = [&](int u, vll &trail) {
    while (!g[u].empty()) {
      int v = g[u].back();
      g[u].pop_back();
      if (!directed) {
        for (int i = 0; i < g[v].size(); i++) {
          if (g[v][i] == u) {
            g[v].erase(g[v].begin() + i);
            break;
          }
        }
      }
      dfs(v, trail);
    }
    trail.push_back(u);
  };
 vll trail;
  dfs(s, trail);
  reverse(trail.begin(), trail.end());
  return trail;
}

int main() {
  cout << fixed << setprecision(20);
  ll N;
  ll a = 1, b = 1;
  ll c = 0;
  ll p = 0;
  string S, T;
  ll M, K;
  ll m;
  ll x, y, z;
  ll t;
  vvll G = {{1,1, 2, 2, 3,3}, {0,0, 2,3}, {0, 0, 1,3}, {0,0, 1,2}};
  /*
  cin >> N>>M;
  rep(i,M){
    cin >> a >b;
    --a,--b;
    G[a].push_back(b),G[b].push_back(a);
  }*/
  auto X = EulerianTrail(0, G,false);
  rep(i, X.size()) cout << X[i] << ' ';
  cout << endl;
}