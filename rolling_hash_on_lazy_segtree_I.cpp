#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); i++)
#define rep(i, n) for (ll i = (0); i < (ll)(n); i++)

template <typename T, typename E>
struct LazySegmentTree {
 private:
  int n{}, sz{}, height{};
  vector<T> data;
  vector<E> lazy;
  T (*op)(T, T);
  T(*e)
  ();
  T(*mapping)
  (E, T);
  E(*composition)
  (E, E);
  E(*id)
  ();

  void update(int k) { data[k] = op(data[2 * k], data[2 * k + 1]); }

  void all_apply(int k, const E x) {
    data[k] = mapping(x, data[k]);
    if (k < sz) lazy[k] = composition(x, lazy[k]);
  }

  void propagate(int k) {
    if (lazy[k] != id()) {
      all_apply(2 * k, lazy[k]);
      all_apply(2 * k + 1, lazy[k]);
      lazy[k] = id();
    }
  }

 public:
  LazySegmentTree() = default;
  explicit LazySegmentTree(int n, T (*op)(T, T), T (*e)(), T (*mapping)(E, T),
                           E (*composition)(E, E), E (*id)())
      : n(n), op(op), mapping(mapping), composition(composition), e(e), id(id) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    data = vector<T>(2 * sz, e());
    lazy = vector<E>(sz, id());
  }

  explicit LazySegmentTree(const vector<T> &v, T (*op)(T, T), T (*e)(),
                           T (*mapping)(E, T), E (*composition)(E, E),
                           E (*id)())
      : LazySegmentTree(v.size(), op, e, mapping, composition, id) {
    build(v);
  }

  void build(const vector<T> &v) {
    assert(n == (int)v.size());
    for (int k = 0; k < n; k++) data[k + sz] = v[k];
    for (int k = sz - 1; k > 0; k--) update(k);
  }

  void set(int k, const T x) {
    assert(0 <= k && k < n);
    k += sz;
    for (int i = height; i > 0; i--) propagate(k >> i);
    data[k] = x;
    for (int i = 1; i <= height; i++) update(k >> i);
  }

  T get(int k) {
    assert(0 <= k && k < n);
    k += sz;
    for (int i = height; i > 0; i--) propagate(k >> i);
    return data[k];
  }

  T operator[](int k) { return get(k); }

  T prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    if (l >= r) return e();
    l += sz;
    r += sz;
    // 更新する区間を部分的に含んだ区間においてトップダウンで子ノードに伝搬させながらdataの値を更新
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) propagate(l >> i);
      if (((r >> i) << i) != r) propagate((r - 1) >> i);
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

  void apply(int k, const E &x) {
    assert(0 <= k && k < n);
    k += sz;
    for (int i = height; i > 0; i--) propagate(k >> i);
    data[k] = mapping(x, data[k]);
    for (int i = 1; i <= height; i++) update(k >> i);
  }

  void apply(int l, int r, E x) {
    if (l >= r) return;
    l += sz;
    r += sz;
    // 更新する区間を部分的に含んだ区間においてトップダウンで子ノードに伝搬させながらdataの値を更新
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) propagate(l >> i);
      if (((r >> i) << i) != r) propagate((r - 1) >> i);
    }
    {
      // 値を更新する区間のdataとlazyの値を更新
      int l2 = l, r2 = r;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) all_apply(l++, x);
        if (r & 1) all_apply(--r, x);
      }
      l = l2, r = r2;
    }
    // 更新する区間を部分的に含んだ区間においてボトムアップで子ノードに伝搬させながらdataの値を更新
    for (int i = 1; i <= height; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }

  template <typename C>
  int max_right(int l, const C check) {
    if (l >= n) return n;
    l += sz;
    for (int i = height; i > 0; i--) propagate(l >> i);
    T sum = e();
    do {
      while ((l & 1) == 0) l >>= 1;
      if (check(op(sum, data[l]))) {
        while (l < sz) {
          propagate(l);
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

  template <typename C>
  int min_left(int r, const C &check) {
    if (r <= 0) return 0;
    r += sz;
    for (int i = height; i > 0; i--) propagate((r - 1) >> i);
    T sum = e();
    do {
      r--;
      while (r > 1 and (r & 1)) r >>= 1;
      if (check(op(data[r], sum))) {
        while (r < sz) {
          propagate(r);
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

namespace rolling_hash_on_lazy_segtree_INVAl {
struct Sx {
  __int128_t value;  // 値
  __int128_t
      x;  // 乱択で選ばれた数をHASHとすると右側にいくつHASYがあるか(説明が難しい)
  __int128_t mod;  // modはmod
                   // 値更新型の遅延セグ木を作りたければ長さを追加する必要もある
};
// 遅延伝搬処理に用いる(値更新とかに使えるのかな...)
using Fx = __int128_t;
// 念のため２つ用意してある(1つで十分だと思う...)
vector<__int128_t> MOD = {(1LL << 61) - 1, 1000000007};
vector<LazySegmentTree<Sx, Fx>> lazyS(2), lazyT(2);
Sx op(Sx a, Sx b) {
  return {((a.value * b.x) % a.mod + b.value) % a.mod, (a.x * b.x) % a.mod,
          a.mod};
}
__int128_t a = randomINT(2, (1LL << 61) - 2);
__int128_t b = randomINT(2, 1000000006);

vector<__int128_t> HASH = {a, b};
// １つ目のmodに対応した単位元
Sx e() { return {0, 1, (1LL << 61) - 1}; }

// 2つ目のmodに対応した単位元
Sx e2() { return {0, 1, 1000000007}; }
Sx mapping(Fx f, Sx x1) { return {x1.value ^ f, x1.x, x1.mod}; }
Fx composition(Fx f, Fx g) { return f ^ g; }

Fx id() { return 0; }
// 参考(https://nyaannyaan.github.io/library/string/rolling-hash-on-segment-tree.hpp.html)
struct rolling_hash_on_lazy_segtree {
 private:
  int n{};
  vector<__int128_t> A, B;

 public:
  rolling_hash_on_lazy_segtree() = default;
  explicit rolling_hash_on_lazy_segtree(int n, vector<__int128_t> A,
                                        vector<__int128_t> B)
      : n(n), A(A), B(B) {
    build(n, A, B);
  };
  explicit rolling_hash_on_lazy_segtree(vector<__int128_t> A,
                                        vector<__int128_t> B)
      : rolling_hash_on_lazy_segtree(A.size(), A, B) {};
  void build(int n, vector<__int128_t> &A, vector<__int128_t> &B) {
    LazySegmentTree<Sx, Fx> r(n, op, e, mapping, composition, id);
    lazyS[0] = r;
    lazyT[0] = r;
    rep(i, A.size()) lazyS[0].set(i, {A[i], a, MOD[0]});
    rep(i, B.size()) lazyT[0].set(i, {B[i], a, MOD[0]});
    LazySegmentTree<Sx, Fx> r2(n, op, e2, mapping, composition, id);
    lazyS[1] = r2;
    lazyT[1] = r2;
    rep(i, A.size()) lazyS[1].set(i, {A[i], b, MOD[1]});
    rep(i, B.size()) lazyT[1].set(i, {B[i], b, MOD[1]});
    return;
  }
  // １番目のk番目の要素をkに変更する
  void setS(int k, __int128_t x) {
    rep(i, 2) lazyS[i].set(k, {x, HASH[i], MOD[i]});
  }
  // 2番目のk番目の要素をkに変更する
  void setT(int k, __int128_t x) {
    rep(i, 2) lazyT[i].set(k, {x, HASH[i], MOD[i]});
  }
  // １番目のi=l..r-1を満たす要素A[i]においてA[i]=f(A[i])の処理を行う
  void applyS(int l, int r, Fx f) { rep(i, 2) lazyS[i].apply(l, r, f); }
  // 2番目のi=l..r-1を満たす要素A[i]においてA[i]=f(A[i])の処理を行う
  void applyT(int l, int r, Fx f) { rep(i, 2) lazyT[i].apply(l, r, f); }
  // i∈[l,r)を満たす１番目の文字列のハッシュ値
  vector<__int128_t> prodS(int l, int r) {
    return {lazyS[0].prod(l, r).value, lazyS[1].prod(l, r).value};
  }
  // i∈[l,r)を満たす2番目の文字列のハッシュ値
  vector<__int128_t> prodT(int l, int r) {
    return {lazyT[0].prod(l, r).value, lazyT[1].prod(l, r).value};
  }
  // i∈[0,n)を満たす１番目の文字列のハッシュ値
  vector<__int128_t> all_prodS() {
    return {lazyS[0].all_prod().value, lazyS[1].all_prod().value};
  }
  // i∈[0,n)を満たす2番目の文字列のハッシュ値
  vector<__int128_t> all_prodT() {
    return {lazyT[0].all_prod().value, lazyT[1].all_prod().value};
  }
  // 1番目の文字列[l,r)と2番目の文字列[l1,r1)の文字列の一致判定
  bool same(int l, int r, int l1, int r1) {
    if (r - l != r1 - l1) return false;
    if (r < l || r1 < l1) return false;
    return prodS(l, r) == prodT(l1, r1);
  }
  // 　1番目のハッシュ値を返す
  __int128_t HASH_S() { return a; }
  // 　2番目のハッシュ値を返す
  __int128_t HASH_T() { return b; }
  // 全てのハッシュの変換
  vector<__int128_t> ALL_HASH() { return HASH; }
};

}  // namespace rolling_hash_on_lazy_segtree_INVAl
   // namespace rolling_hash_on_lazy_segtree_INVAl
using rolling_hash_on_lazy_segtree_INVAl::rolling_hash_on_lazy_segtree;