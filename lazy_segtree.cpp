#include <bits/stdc++.h>
using namespace std;
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
  int max_right(int l, const C &check) {
    if (l >= n) return n;
    l += sz;

    for (int i = height; i > 0; i--) propagate(l >> i);
    T sum = e();
    do {
      while ((l & 1) == 0) l >>= 1;
      if (!check(op(sum, data[l]))) {
        while (l < sz) {
          propagate(l);
          l <<= 1;
          auto nxt = op(sum, data[l]);
          if (check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l - sz;
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
      if (!check(op(data[r], sum))) {
        while (r < sz) {
          propagate(r);
          r = (r << 1) + 1;
          auto nxt = op(data[r], sum);
          if (check(nxt)) {
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