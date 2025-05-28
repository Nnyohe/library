// 完全グラフの内頂点数が最大になるような頂点数を返す。
// 計算量O(2^(sqrt(2*M))*N)
//  参考：https://ei1333.github.io/luzhiled/snippets/graph/maximum-clique.html
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
using vvvvll = vector<vvvll>;
using vvvvvll = vector<vvvvll>;
using vd = vector<double>;
using vvd = vector<vd>;
using vvvd = vector<vvd>;
using vld = vector<long double>;
using vvld = vector<vld>;
using vvvld = vector<vvld>;
using vc = vector<char>;
using vvc = vector<vc>;
using lll = __int128_t;
using vs = vector<string>;
using pii = pair<long long, long long>;
using mint = modint1000000007;
template <typename T>
T maximum_clique(vvb g, function<T(vector<int>)> f) {
  int N = (int)g.size(), M = 0;
  vector<int> deg(N), v(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < i; j++) {
      assert(g[i][j] == g[j][i]);
      if (g[i][j]) {
        ++deg[i];
        ++M;
      }
    }
  }
  T t = 0;
  int lim = (int)sqrt(2 * M);

  for (int i = 0; i < N; i++) {
    vector<int> notice;
    for (int j = 0; j < N; j++) {
      if (!v[j] && deg[j] < lim) {
        for (int k = 0; k < N; k++) {
          if (j == k) continue;
          if (g[j][k]) notice.emplace_back(k);
        }
        notice.emplace_back(j);
        break;
      }
    }
    if (notice.empty()) break;
    int neighbor = (int)notice.size() - 1;
    vector<int> bit(neighbor);
    for (int j = 0; j < neighbor; j++) {
      for (int k = 0; k < j; k++) {
        if (!g[notice[j]][notice[k]]) {
          bit[j] |= 1 << k;
          bit[k] |= 1 << j;
        }
      }
    }
    for (int j = 0; j < (1 << neighbor); j++) {
      bool ok = true;
      for (int k = 0; k < neighbor; k++) {
        if ((j >> k) & 1) ok &= (j & bit[k]) == 0;
      }
      if (ok) {
        vector<int> stock{notice.back()};
        for (int k = 0; k < neighbor; k++) {
          if ((j >> k) & 1) stock.emplace_back(notice[k]);
        }
        t = max(t, f(stock));
      }
    }
    v[notice.back()] = true;
    for (int j = 0; j < N; j++) {
      if (g[j][notice.back()]) {
        --deg[j];
        g[notice.back()][j] = g[j][notice.back()] = false;
      }
    }
  }

  vector<int> notice;
  for (int j = 0; j < N; j++) {
    if (!v[j]) notice.emplace_back(j);
  }
  int neighbor = (int)notice.size();
  vector<int> bit(neighbor);
  for (int j = 0; j < neighbor; j++) {
    for (int k = 0; k < j; k++) {
      if (!g[notice[j]][notice[k]]) {
        bit[j] |= 1 << k;
        bit[k] |= 1 << j;
      }
    }
  }
  for (int j = 0; j < (1 << neighbor); j++) {
    bool ok = true;
    for (int k = 0; k < neighbor; k++) {
      if ((j >> k) & 1) ok &= (j & bit[k]) == 0;
    }
    if (ok) {
      vector<int> stock;
      for (int k = 0; k < neighbor; k++) {
        if ((j >> k) & 1) stock.emplace_back(notice[k]);
      }
      t = max(t, f(stock));
    }
  }
  //tがmaxなものstockは最大クリークを満たす点の集合を表す
  return t;
}
int main() {
  cout << fixed << setprecision(20);
  ll a = 0, b = 0;
  ll a2, b2;
  ll a1 = 0, b1 = 0;
  ll c = 0, c1;
  ll p = 1;
  ll W;
  ll N, M;
  ll t;
  ll K;
  ll h, w;
  ll L;
  string S, T;
  cin >> N >> M;
  vvb X(N, vb(N, false));
  vvll G(N);
  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    X[a][b] = true, X[b][a] = true;
    G[a].push_back(b), G[b].push_back(a);
  }
  function<int(vector<int>)> f = [](vector<int> t) { return t.size(); };
  ll ans = maximum_clique(X, f);
}