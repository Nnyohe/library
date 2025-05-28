// ちゃんと確認する！！
//  抽象化segtree beats
//解答例
// https :  // yukicoder.me/problems/no/880
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (ll i = (0); i < (ll)(n); i++)
// 参考：　https://smijake3.hatenablog.com/entry/2019/04/28/021457
namespace Segment_Tree_Beats_INVAl {
// 型の指定
using R = long long;
R inf = 1e9 + 100;
// deta・RSQ 用の型
struct T {
  // 区間最大値
  R sum;
  // 区間最小公倍数
  R left;
  // 区間最大値
  R Max;
  // 区間の長さ
  R len;
  // 更新処理が正当か否かを判別する
  bool same;
  // 区間内に存在する要素が同じであるかどうかを判別する
  bool same2;
  T(R x, R _size = 1)
      : sum(x * _size), left(x), Max(x), len(_size), same(true), same2(true) {}
  T() : sum(0), left(1), Max(0), len(0), same(true), same2(true) {}
};

// モノイドの結合律(足し算とか掛け算とか)
T op(T a, T b) {
  if (a.len == 0) return b;
  if (b.len == 0) return a;
  T ret;

  ret.sum = a.sum + b.sum;
  ret.left = min(lcm(a.left, b.left), inf);
  ret.Max = max(a.Max, b.Max);
  ret.len = a.len + b.len;
  ret.same2 = (a.left == b.left && a.same2 && b.same2);
  return ret;
}
// モノイドの単位元
T e() { return T(); }

// 任意の遅延伝搬用の型
struct E {
  R togcd;
  R set;
  E() : togcd(0), set(0) {}
  E(R g, R up) : togcd(g), set(up) {}
  static E GCD(R g) { return E(g, 0); }
  static E update(R g) { return E(0, g); }
};
// dataに対する遅延伝搬(今回は除算を行うので長さは必要)
// 要素単体の更新は長さ１の区間の更新ととらえればいい。
T mapping(E a, T b) {
  // 　正確に処理できないものが確実な時は飛ばしていい
  if (!b.same) return b;
  if (a.set) b = T(a.set, b.len);
  if (a.togcd) {
    // 区間の要素が全て同じならば単純にその要素と最大公約数との最大公約数にupdateすればよい
    if (b.same2) {
      b = T(gcd(b.Max, a.togcd), b.len);
    } else if (b.left == inf or a.togcd % b.left)
      b.same = false;
  }
  return b;
}
// fnewが後の操作
E composition(E fnew, E fold) {
  // setとgcd処理は両方とも同時に持たないようにしておく(片方は確実に0)
  ;
  // 後の方に更新処理が存在する場合、前の方の処理を棄却する
  if (fnew.set) {
    return E::update(fnew.set);
  }  // 後の方に更新処理が存在せず、前の方に更新処理を行う場合、前の更新操作を行ってから後の方の操作でgcd操作を行うので実質gcdの値を更新処理する動作と同じになる。
  else if (fold.set) {
    return E::update(gcd(fnew.togcd, fold.set));
  } else  // 前も後ろも更新処理がない場合はgcd処理のみを考えればいい、前のgcdと後のgcd二回の操作を一回にまとめる
    return E::GCD(gcd(fnew.togcd, fold.togcd));
}
E id() { return E(); }

struct Segment_Tree_Beats {
 private:
  int n, sz, height;
  vector<T> data;

  // 任意の遅延伝搬(単位元はid())
  vector<E> lazy;
  void update(int k) { data[k] = op(data[2 * k], data[2 * k + 1]); }

  void push(int k) {
    all_apply(2 * k, lazy[k]);
    all_apply(2 * k + 1, lazy[k]);
    lazy[k] = id();
  }

  // 抽象遅延伝搬作業
  void all_apply(int k, E x) {
    data[k] = mapping(x, data[k]);
    if (k < sz) {
      lazy[k] = composition(x, lazy[k]);
      if (!data[k].same) {
        push(k);
        update(k);
      }
    }
  }

 public:
  Segment_Tree_Beats() = default;

  explicit Segment_Tree_Beats(int n) : Segment_Tree_Beats(vector<R>(n, 0)) {}
  explicit Segment_Tree_Beats(const vector<R> &v) : n(v.size()) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    data = vector<T>(2 * sz, e());
    lazy = vector<E>(sz, id());
    build(v);
  }

  void build(const vector<R> &v) {
    assert(n == (int)v.size());
    for (int k = 0; k < n; k++) {
      data[k + sz] = T(v[k]);
    }
    for (int k = sz - 1; k > 0; k--) update(k);
  }

  void set(int k, const T x) {
    assert(0 <= k && k < n);
    k += sz;
    for (int i = height; i > 0; i--) push(k >> i);
    data[k] = x;
    for (int i = 1; i <= height; i++) update(k >> i);
  }

  T get(int k) {
    assert(0 <= k && k < n);
    k += sz;
    for (int i = height; i > 0; i--) push(k >> i);
    return data[k];
  }

  T operator[](int k) { return get(k); }

  // i=l,...r-1においてmapping(x,v[i])
  void apply(int l, int r, E x) {
    if (l >= r) return;
    l += sz;
    r += sz;
    // 更新する区間を部分的に含んだ区間においてトップダウンで子ノードに伝搬させながらdataの値を更新
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }

    // 値を更新する区間のdataとlazyの値を更新
    int l2 = l, r2 = r;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) all_apply(l++, x);
      if (r & 1) all_apply(--r, x);
    }
    l = l2, r = r2;

    // 更新する区間を部分的に含んだ区間においてボトムアップで子ノードに伝搬させながらdataの値を更新
    for (int i = 1; i <= height; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }
  // op(A[l],A[l+1],...,A[r-1])を求める
  T prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    if (l >= r) return e();
    l += sz;
    r += sz;

    // 更新する区間を部分的に含んだ区間においてトップダウンで子ノードに伝搬させながらdataの値を更新
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }

    T L = e(), R = e();
    // 値をチェックする区間のdataの値をチェック
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = op(L, data[l++]);
      if (r & 1) R = op(data[--r], R);
    }
    return op(L, R);
  }

  T all_prod() const { return data[1]; }
  // lに対しcheck(op(A[l],A[l+1],...A[r]))=trueとなる最大のrを返す
  template <typename C>
  int max_right(int l, const C check) {
    if (l >= n) return n;
    l += sz;
    for (int i = height; i > 0; i--) push(l >> i);
    T sum = e();
    do {
      while ((l & 1) == 0) l >>= 1;
      if (check(op(sum, data[l]))) {
        while (l < sz) {
          push(l);
          l <<= 1;
          auto nxt = op(sum, data[l]);
          if (not check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l + 1 - sz;
      }
      sum = op(sum, data[l++]);
    } while ((l & -l) != l);
    return n;
  }
  // rに対しcheck(op(A[l],A[l+1],...A[r]))=trueとなる最小のlを返す
  template <typename C>
  int min_left(int r, const C &check) {
    if (r <= 0) return 0;
    r += sz;
    for (int i = height; i > 0; i--) push((r - 1) >> i);
    T sum = e();
    do {
      r--;
      while (r > 1 and (r & 1)) r >>= 1;
      if (check(op(data[r], sum))) {
        while (r < sz) {
          push(r);
          r = (r << 1) + 1;
          auto nxt = op(data[r], sum);
          if (not check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = op(data[r], sum);
    } while ((r & -r) != r);
    return 0;
  }
};

}   //namespace Segment_Tree_Beats_INVAl
using Segment_Tree_Beats_INVAl::Segment_Tree_Beats;
// set(k,x) A[k]=xに更新
// get(k,x) A[k]を返す
// prod(l,r) : op(A[l],A[l+1],...,A[r-1])を求める
// apply(l,r,x) : i=l,...r-1においてmapping(x,A[i])を実行
// max_right(l,C) :
// lに対しcheck(op(A[l],A[l+1],...A[r]))=trueとなる最大のrを返す
// min_left(r, C) :
// rに対しcheck(op(A[l],A[l+1],...A[r]))=trueとなる最小のlを返す

// Sはdataを表している。
using ll = long long;
using vll = vector<ll>;

using R = ll;

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
  cin >> N >> t;
  vll A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  // cout << A.size() << endl;
  Segment_Tree_Beats seg(A);
  rep(_, t) {
    ll d;
    cin >> a >> b >> c;
    --b;
    if (a == 1) {
      cin >> d;
      seg.apply(b, c, Segment_Tree_Beats_INVAl::E::update(d));
    }
    if (a == 2) {
      cin >> d;
      seg.apply(b, c, Segment_Tree_Beats_INVAl::E::GCD(d));
    }
    if (a == 3) {
      // cin >> d;
      cout << seg.prod(b, c).Max << endl;
    }
    if (a == 4) {
      //   cin >> d;
      cout << seg.prod(b, c).sum << endl;
    }
  }
}