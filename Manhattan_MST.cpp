// 2次元平面上の頂点たちのマンハッタン距離による最小全域木を求めるアルゴリズム
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
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
const long double PI = acos(-1.0L);
const long double EPS = 1e-10;
const double INF = 1e18;

template <typename T>
vector<vector<pair<T, T>>> Manhattan_MST(vector<pair<T, T>> &XY) {
    int N = XY.size();
    vector<tuple<T, int, int>> dat;
    dat.resize(4 * N);
    vector<int> idx(N);
    iota(ALL(idx), 0);
    rep(a, 2) {
        for (auto &&[x, y] : XY) x = -x;
        rep(b, 2) {
            for (auto &&[x, y] : XY) swap(x, y);
            sort(ALL(idx), [&](const int &i, const int &j) -> bool {
                return XY[i].first + XY[i].second < XY[j].first + XY[j].second;
            });
            map<T, int> mp;
            for (const int i : idx) {
                auto &[x, y] = XY[i];
                for (auto it = mp.lower_bound(-y); it != mp.end();
                     it = mp.erase(it)) {
                    const int j = it->second;
                    auto &[xj, yj] = XY[j];
                    const int dx = x - xj;
                    const int dy = y - yj;
                    if (dy > dx) break;
                    dat.emplace_back(dx + dy, i, j);
                }
                mp[-y] = i;
            }
        }
    }
    sort(ALL(dat));
    vector<vector<pair<T, T>>> G(N);
    dsu d(N);
    for (auto &&[cost, i, j] : dat) {
        if (!d.same(i, j)) {
            G[i].push_back({j, cost});
            G[j].push_back({i, cost});
            d.merge(i, j);
        }
    }
    return G;
}

int main() {
    cout << fixed << setprecision(20);
    ll a = 0, b = 0;
    ll a2, b2;
    ll a1, b1;
    ll c = 0;
    ll f;
    ll p = 1;
    ll W;
    ll K;
    ll N, M;
    ll L;
    cin >> N;
    vll X, Y;
    vll P(N);
    vector<pair<ll, ll>> XY;
    rep(i, N) {
        cin >> a;
        XY.emplace_back(a, i);
    }
    auto G = Manhattan_MST(XY);
    vll Ans(N, INF);
    for (auto I : G) {
        for (auto U : I) {
            Ans[U.first] = min(Ans[U.first], U.second);
        }
    }
    for (auto ans : Ans) {
        cout << ans << ' ';
    }
    cout << endl;
}