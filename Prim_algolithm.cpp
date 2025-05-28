#include <bits/stdc++.h>
using namespace std;

using ll = long long;
struct PRIM {
  ll cost;
  ll to;
  ll from;
};
bool operator>(const PRIM &r, const PRIM &l) { return r.cost > l.cost; }
bool operator<(const PRIM &r, const PRIM &l) { return r.cost < l.cost; }
// プリム法
// 最小全域木問題の最適解を求める
// 　普段使っているのはクラスカル法だが今後使うかもしれないので習得する
// Gの構成要素は{到着点、コストする}
ll Prim(vector<vector<pair<ll, ll>>> &G) {
  vector<int> A(G.size(), 0);
  A[0] = 1;
  ll sum = 0;
  // 最小全域木のグラフを表す
  vector<vector<pair<ll, ll>>> finG(G.size());
  priority_queue<PRIM, vector<PRIM>, greater<PRIM>> Q;
  for (auto u : G[0]) {
    Q.emplace(u.second, u.first, 0);
  }
  while (!Q.empty()) {
    auto U = Q.top();
    Q.pop();
    if (A[U.to]) continue;
    sum += U.cost;
    finG[U.from].emplace_back(U.to, U.cost);
    finG[U.to].emplace_back(U.from, U.cost);
    A[U.to] = 1;
    for (auto u : G[U.to]) {
      if (A[u.first] == 0) {
        Q.emplace(u.second, u.first, U.to);
      }
    }
  }
  return sum;
}
