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
// 行列累乗
//  A*Bの計算
template <typename T>
vector<vector<T>> mul(vector<vector<T>> A, vector<vector<T>> B) {
  vector<vector<T>> C(A.size(), vector<T>(B[0].size(), 0));
  rep(i, A.size()) {
    rep(k, B.size()) {
      rep(j, B[0].size()) { C[i][j] += (A[i][k] * B[k][j]); }
    }
  }
  return C;
}
// A^nの計算
template <typename T>
vector<vector<T>> POW(vector<vector<T>> A, ll n) {
  vector<vector<T>> B(A.size(), vector<T>(A.size(),0));
  rep(i, A.size()) { B[i][i] = 1; }
  while (n > 0) {
    if (n & 1) B = mul(B, A);
    A = mul(A, A);
    n /= 2;
  }
  return B;
}

/*行列累乗ここまで*/