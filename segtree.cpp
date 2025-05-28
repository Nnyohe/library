#include <bits/stdc++.h>
using namespace std;
// 　抽象化セグメント木
template <typename T>
struct segment_tree {
 private:
  int n{}, sz{}, height{};
  vector<T> node;
  T (*combine)(T, T);  // 区間の結合を行う演算
  T(*identity)
  ();  // 単位元
  void update(int k) { node[k] = combine(node[2 * k], node[2 * k + 1]); }

 public:
  segment_tree(int n, T (*combine)(T, T), T (*identity)())
      : n(n), combine(combine), identity(identity) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    node = vector<T>(2 * sz, identity());
  }
  segment_tree(vector<T> &A, T (*combine)(T, T), T (*identity)())
      : n((int)A.size()),
        combine(combine),
        identity(identity) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    node = vector<T>(2 * sz, identity());

    for (int i = 0; i < (int)A.size(); i++) {
      node[sz + i] = A[i];
    }
    for (int i = sz - 1; i > 0; --i) {
      node[i] = combine(node[2 * i], node[2 * i + 1]);
    }
  }
  T get(int k) { return node[k + sz]; }
  T operator[](int i) {
    assert(0 <= i && i < n);
    return node[i + sz];
  }

  void set(int i, T x) {
    assert(0 <= i && i < n);
    i += sz;
    node[i] = x;
    for (int k = 1; k <= height; k++) update(i >> k);
  }

  T prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    T res = identity();  // 初期値は単位元
    T res2 = identity();

    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      // 区間内のものを左右から結合
      if (l & 1) res = combine(res, node[l++]);
      if (r & 1) res2 = combine(node[--r], res2);
    }
    return combine(res, res2);
  }
  T all_prod() { return prod(0, n); }

  template <typename C>
  int max_right(int l, const C &check) {
    if (l >= n) return n;
    l += sz;

    T sum = identity();
    do {
      while ((l & 1) == 0) l >>= 1;
      if (!check(op(sum, node[l]))) {
        while (l < sz) {
          l <<= 1;
          auto nxt = op(sum, node[l]);
          if (check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l - sz;
      }
      sum = op(sum, node[l++]);
    } while ((l & -l) != l);
    return n;
  }

  template <typename C>
  int min_left(int r, const C &check) {
    if (r <= 0) return 0;
    r += sz;
    T sum = identity();
    do {
      r--;
      while (r > 1 and (r & 1)) r >>= 1;
      if (!check(op(node[r], sum))) {
        while (r < sz) {
          r = (r << 1) + 1;
          auto nxt = op(node[r], sum);
          if (check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = op(node[r], sum);
    } while ((r & -r) != r);
    return 0;
  }
};
long op(long a, long b) { return max(a, b); }
long e() { return 0; }
int main() {
  int N, t;
  cin >> N >> t;
  segment_tree<long> seg(N, op, e);
  while (t--) {
    int a, b, c;
    cin >> a >> b >> c;
    --b;
    --c;
    if (a == 1)
      seg.set(b, c), cout << seg.get(b) << endl;

    else
      cout << seg.prod(b, c) << endl;
  }
}
