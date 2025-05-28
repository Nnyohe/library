#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
#include <cassert>
#include <functional>
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
void output(T &W, bool x) {
  cout << W;
  if (!x)
    cout << ' ';
  else
    cout << endl;
  return;
}
// sは改行するか否かを表す
template <class T>
void output(vector<T> &W, bool s) {
  rep(i, W.size()) { output(W[i], ((i == W.size() - 1) || s)); }
  return;
}
// sは改行するか否かを表す
template <class T>
void output(vector<vector<T>> &W, bool s) {
  rep(i, W.size()) { output(W[i], s); }
  return;
}
template <class T>
T vectorsum(vector<T> &W, int a, int b) {
  return accumulate(W.begin() + a, W.end() + b, (T)0);
}
template <class T>
T vectorsum(vector<T> &W) {
  int b = W.size();
  return accumulate(ALL(W), (T)0);
}
template <class T>
inline T CHMAX(T &a, const T b) {
  return a = (a < b) ? b : a;
}
template <class T>
inline T CHMIN(T &a, const T b) {
  return a = (a > b) ? b : a;
}
template <class T>
void input(T &W) {
  cin >> W;
  return;
}

template <class T>
void input(vector<T> &W) {
  for (auto &u : W) input(u);
  return;
}
template <class T, class TT>
void add(T &W, TT &a) {
  W += a;
  return;
}
template <class T>
void add(vector<T> &W, vector<T> &a) {
  rep(i, W.size()) add(W[i], a[i]);
}
template <class T>
void add(T &W, T &a) {
  W += a;
}
template <class T, class TT>
void add(vector<T> &W, TT a) {
  for (auto &u : W) add(u, a);
  return;
}
template <class T, class TT>
void mul(T &W, TT &a) {
  W *= a;
  return;
}
template <class T, class TT>
void mul(vector<T> &W, TT a) {
  for (auto &u : W) mul(u, a);
  return;
}
// ！！！使うときは入力の形式を確認すること！！！
//  辺の入力からグラフの生成まで行う関数
//   index: 0-indexか1-indexか
//       q: 無向グラフ(0)か有効グラフ(1か
void makeGraph(vvll &G, ll M, int index, int q) {
  vvll X(M, vll(2, 0));
  input(X);
  if (index == 0) add(X, -1);
  rep(i, M) {
    G[X[i][0]].push_back(X[i][1]);
    if (q == 0) G[X[i][1]].push_back(X[i][0]);
  }
}

const double PI = acos(-1.0L);
const long double EPS = 1e-10;
const double INF = 1e18;

#define LOOP(n) REPI($_, (n))

#define REPI(i, n) \
  for (int i = 0, i##_length = static_cast<int>(n); i < i##_length; ++i)
#define REPF(i, l, r)                                                        \
  for (std::common_type_t<decltype(l), decltype(r)> i = (l), i##_last = (r); \
       i < i##_last; ++i)
#define REPIS(i, l, r, s)                                        \
  for (std::common_type_t<decltype(l), decltype(r), decltype(s)> \
           i = (l),                                              \
           i##_last = (r);                                       \
       i < i##_last; i += (s))

#define REPR(i, n) for (auto i = (n); --i >= 0;)
#define REPB(i, l, r)                                                        \
  for (std::common_type_t<decltype(l), decltype(r)> i = (r), i##_last = (l); \
       --i >= i##_last;)
#define REPRS(i, l, r, s)                                        \
  for (std::common_type_t<decltype(l), decltype(r), decltype(s)> \
           i = (l) + ((r) - (l) - 1) / (s) * (s),                \
           i##_last = (l);                                       \
       i >= i##_last; (i -= (s)))

#define REP(...) $OVERLOAD4(__VA_ARGS__, REPIS, REPF, REPI, LOOP)(__VA_ARGS__)
#define REPD(...) $OVERLOAD4(__VA_ARGS__, REPRS, REPB, REPR)(__VA_ARGS__)

#define FORO(i, n) \
  for (int i = 0, i##_last = static_cast<int>(n); i <= i##_last; ++i)
#define FORI(i, l, r)                                                        \
  for (std::common_type_t<decltype(l), decltype(r)> i = (l), i##_last = (r); \
       i <= i##_last; ++i)
#define FORIS(i, l, r, s)                                        \
  for (std::common_type_t<decltype(l), decltype(r), decltype(s)> \
           i = (l),                                              \
           i##_last = (r);                                       \
       i <= i##_last; i += (s))

#define FORRO(i, n) for (auto i = (n); i >= 0; --i)
#define FORR(i, l, r)                                                        \
  for (std::common_type_t<decltype(l), decltype(r)> i = (r), i##_last = (l); \
       i >= i##_last; --i)
#define FORRS(i, l, r, s)                                        \
  for (std::common_type_t<decltype(l), decltype(r), decltype(s)> \
           i = (l) + ((r) - (l)) / (s) * (s),                    \
           i##_last = (l);                                       \
       i >= i##_last; i -= (s))

#define FOR(...) $OVERLOAD4(__VA_ARGS__, FORIS, FORI, FORO)(__VA_ARGS__)
#define FORD(...) $OVERLOAD4(__VA_ARGS__, FORRS, FORR, FORRO)(__VA_ARGS__)

#define ITR1(e0, v) for (const auto &e0 : (v))
#define ITRP1(e0, v) for (auto e0 : (v))
#define ITRR1(e0, v) for (auto &e0 : (v))

#define ITR2(e0, e1, v) for (const auto [e0, e1] : (v))
#define ITRP2(e0, e1, v) for (auto [e0, e1] : (v))
#define ITRR2(e0, e1, v) for (auto &[e0, e1] : (v))

#define ITR3(e0, e1, e2, v) for (const auto [e0, e1, e2] : (v))
#define ITRP3(e0, e1, e2, v) for (auto [e0, e1, e2] : (v))
#define ITRR3(e0, e1, e2, v) for (auto &[e0, e1, e2] : (v))

#define ITR4(e0, e1, e2, e3, v) for (const auto [e0, e1, e2, e3] : (v))
#define ITRP4(e0, e1, e2, e3, v) for (auto [e0, e1, e2, e3] : (v))
#define ITRR4(e0, e1, e2, e3, v) for (auto &[e0, e1, e2, e3] : (v))

#define ITR(...) $OVERLOAD5(__VA_ARGS__, ITR4, ITR3, ITR2, ITR1)(__VA_ARGS__)
#define ITRP(...) \
  $OVERLOAD5(__VA_ARGS__, ITRP4, ITRP3, ITRP2, ITRP1)(__VA_ARGS__)
#define ITRR(...) \
  $OVERLOAD5(__VA_ARGS__, ITRR4, ITRR3, ITRR2, ITRR1)(__VA_ARGS__)

long long Power(long long a, long long b, long long m) {
  long long p = a, Answer = 1;
  for (int i = 0; i < 63; i++) {
    ll wari = (1LL << i);
    if ((b / wari) % 2 == 1) {
      Answer %= m;
      Answer = (Answer * p) % m;  // 「a の 2^i 乗」が掛けられるとき
    }
    p %= m;
    p = (p * p) % m;
  }
  return Answer;
}
void Yes(bool b) {
  if (b)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
}
template <typename T>
vector<T> dycstra(vector<vector<pair<ll, T>>> G, ll N, ll K) {
  vb kaku(N, false);
  vector<T> cur(N, INF);
  cur[K] = 0;
  priority_queue<pair<T, ll>, vector<pair<T, ll>>, greater<pair<T, ll>>> Q;
  Q.push(make_pair(cur[K], K));
  while (!Q.empty()) {
    ll pos = Q.top().second;
    Q.pop();
    if (kaku[pos]) continue;
    kaku[pos] = true;
    for (ll i = 0; i < G[pos].size(); i++) {
      ll nex = G[pos][i].first;
      T cost = G[pos][i].second;
      if (cur[nex] > cur[pos] + cost - EPS) {
        cur[nex] = cur[pos] + cost;
        Q.push(make_pair(cur[nex], nex));
      }
    }
  }
  return cur;
}
random_device seed;
mt19937_64 engine(seed());
ll randamX(ll K) {
  ll a = engine();
  a %= (K - 1);
  a++;
  return a;
}

template <typename T>
// [0,M)についての階上を求める
vector<T> KAI(int M) {
  vector<T> kai(M, 1);
  rep(i, M - 1) { kai[i + 1] = kai[i] * (i + 1); }
  return kai;
}
template <typename T>
vector<T> DIV(int M) {
  vector<T> kai = KAI<T>(M), div(M, 1);

  rep(i, M - 1) { div[i + 1] = 1 / kai[i + 1]; }
  return div;
}
/*  関数名          n_ary(string str, int n, int m)
    説明            n 進数で表現された数値を文字列 str で受け取り、m
   進数に直して文字列で出力する。 使用ライブラリ  string 使用自作関数    ntodec,
   decton, pow_ll 制約事項        36進数までの対応。負の値には対応していない。
*/
string n_ary(string &str, int n, int m) {
  str = "";
  while (n) {
    str.push_back('0' + n % m);
    n /= m;
  }
  reverse(ALL(str));
  return str;
}

template <typename T>
vector<T> compress(vector<T> &X) {
  // ソートした結果を vals に
  vector<T> vals = X;
  sort(vals.begin(), vals.end());
  // 隣り合う重複を削除(unique), 末端のゴミを削除(erase)
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  // 各要素ごとに二分探索で位置を求める
  for (int i = 0; i < (int)X.size(); i++) {
    X[i] = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
  }
  return vals;
}

/*行列累乗ここまで*/
// 0-1BFS
vll BFS(vvll G, ll a) {
  ll n = G.size();
  vector<ll> X(n, INF);
  X[a] = 0;
  queue<ll> Q;
  Q.push(a);
  while (!Q.empty()) {
    ll cur = Q.front();
    Q.pop();
    for (auto next : G[cur]) {
      if (X[cur] + 1 < X[next]) {
        X[next] = X[cur] + 1;
        Q.push(next);
      }
    }
  }
  return X;
}
long long extGCD(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long d = extGCD(b, a % b, y, x);
  y -= a / b * x;
  return d;
}
std::ostream &operator<<(std::ostream &dest, __int128_t value) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (value < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}
// 削除可能priorty_queue
struct eraseable_priority_queue {
  priority_queue<ll> Q1, Q2;
  void push(ll K) { Q1.emplace(K); }
  void erase(ll K) { Q2.emplace(K); }
  ll top() {
    while (!Q1.empty() && Q2.top() != Q1.top()) Q1.pop(), Q2.pop();
    return Q1.top();
  }
  bool empty() {
    while (!Q1.empty() && Q2.top() != Q1.top()) Q1.pop(), Q2.pop();
    return Q1.empty();
  }
};

struct TRI {
  ll a;
  ll b;
  ll c;
  ll d;
};
bool operator>(const TRI &r, const TRI &l) {
  return (r.a > l.a | (r.a == l.a & r.b > l.b) |
          (r.a == l.a & r.b == l.b & r.c > l.c));
}
bool operator<(const TRI &r, const TRI &l) {
  return (r.a < l.a | (r.a == l.a & r.b < l.b) |
          (r.a == l.a & r.b == l.b & r.c < l.c));
}

// Sはdataを表している。
using S = pair<ll, ll>;
using F = pair<ll, ll>;

ll op(ll a, ll b) { return a + b; }

ll e() { return 0; }
S mapping(F f, S x) { return f; }
F composition(F f, F g) { return g; }
F id() { return (pair<ll, ll>){(ll)INF, 0LL}; }
ll half = 499122177;
vll dx = {0, 0, 1, -1};
vll dy = {1, -1, 0, 0};
int target;
bool f(int v) { return v < target; }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(20);
  ll a = 0, b = 0;
  ll a2, b2, c2;
  ll a1 = 0, b1 = 0;
  ll c = 0, c1;
  ll p = 1;
  ll N, M;
  ll t;
  ll K;
  ll h, w;
  ll L;
  string S, T;
  cin >> N >> M >> t;
  dsu d(N);
  vector<TRI> P;
  rep(i, M) {
    cin >> a >> b >> c;
    --a, --b;
    P.emplace_back(c, a, b, 0);
  }
  vector<vector<pair<ll, ll>>> G(N);
  sort(ALL(P));
  rep(i, M) {
    if (!d.same(P[i].b, P[i].c)) {
      d.merge(P[i].b, P[i].c);
      G[P[i].b].emplace_back(P[i].c, P[i].a);
      G[P[i].c].emplace_back(P[i].b, P[i].a);
    }
  }
  vector<pair<ll, ll>> pa(N, {-1, -1});
  vll depth(N, 0);
  auto dfs = [&](auto dfs, ll cur, ll parent) -> void {
    for (auto u : G[cur]) {
      if (u.first != parent) {
        pa[u.first] = {cur, u.second};
        depth[u.first] = depth[cur] + 1;
        dfs(dfs, u.first, cur);
      }
    }
  };
  dfs(dfs, 0, -1);
  vector<vector<pair<ll, ll>>> dp(N, vector<pair<ll, ll>>(30, {0, -1}));
  rep(i, N) { dp[i][0] = pa[i]; }
  rep(k, 29) {
    rep(i, N) {
      if (dp[i][k].first != -1)
        dp[i][k + 1] = {dp[dp[i][k].first][k].first,
                        max(dp[dp[i][k].first][k].second, dp[i][k].second)};
    }
  }
  auto value = [&](ll &cur, ll depth) -> ll {
    ll sum = 0;
    rep(k, 30) {
      if (depth & (1LL << k)) {
        sum = max(sum, dp[cur][k].second);
        cur = dp[cur][k].first;
      }
    }
    return sum;
  };
  rep(i, t) {
    cin >> a >> b >> c;
    --a, --b;
    ll sum;

    if (depth[a] > depth[b])
      sum = value(a, depth[a] - depth[b]);
    else
      sum = value(b, -depth[a] + depth[b]);
    if (a != b) {
      for (int k = 29; k > -1; k--) {
        if (dp[a][k].first != dp[b][k].first) {
          sum = max({sum, dp[a][k].second, dp[b][k].second});
          a = dp[a][k].first, b = dp[b][k].first;
        }
      }
      sum = max({sum, dp[a][0].second, dp[b][0].second});
    }
    Yes(sum > c);
  }
}