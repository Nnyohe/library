//２部グラフの判定、２部グラフならば片方の個数を返す。否なら-1を返す
//計算量O(V+E)
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
#include <iostream>
using namespace atcoder;
using ll = long long;
using ld = long double;
using P = pair<int, int>;
using Graph = vector<vector<int>>;
using vi = vector<int>;
using vl = vector<long>;
using vll = vector<long long>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vvb = vector<vb>;
using vvll = vector<vll>;
using vvvll = vector<vvll>;
using vc = vector<char>;
using vvc = vector<vc>;
using vs = vector<string>;
using pii = pair<long long, long long>;
using mint = modint1000000007;
const long double EPS = 1e-10;
const long long INF = 1e18;
const long double PI = acos(-1.0L);
#define mp make_pair
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); i++)
#define rep(i, n) for (ll i = (0); i < (ll)(n); i++)
#define rrep(i, n) for (ll i = (1); i < (ll)(n + 1); i++)
#define repd(i, n) for (ll i = n - 1; i >= 0; i--)
#define rrepd(i, n) for (ll i = n; i >= 1; i--)
#define ALL(n) begin(n), end(n)
#define fore(i, a) for (auto &i : a)
#define IN(a, x, b) (a <= x && x < b)
#define IN(a, x, b) (a <= x && x < b)
#define INIT                        \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0);

using namespace std;
int BipartiteGraph(const vector<vector<int>> &g) {
  int n = g.size();
  vector<int> color(n, -1);
  int white_cnt = 0;
  function<bool(int, int, int)> dfs = [&](int u, int prev, int c) {
    color[u] = c;
    if (c == 1) white_cnt++;
    for (auto v : g[u])
      if (v != prev) {
        if (color[v] == -1) {
          if (!dfs(v, u, 1 - c)) return false;
        } else if (color[v] != 1 - c) {
          return false;
        }
      }
    return true;
  };
  bool x = true;
  rep(i, n) {
    if (color[x] == -1) {
      x &= dfs(i, -1, 0);
    }
    if (!x) return -1;
    return white_cnt;
  }
}