#include <bits/stdc++.h>
using namespace std;
// 参考：　https://smijake3.hatenablog.com/entry/2019/04/28/021457
namespace Segment_Tree_Beats_INVAl {
// sumの型の指定
using R = long long;
// deta・RSQ 用の型
using T = long long;
// 任意の遅延伝搬用の型
using E = long long;
// モノイドの結合律(足し算とか掛け算とか)
T op(T a, T b) { return a + b; }
// モノイドの単位元
T e() { return 0; }
// max,minの更新処置によってデータそのものに影響を与える関数(データの値、更新値、最大（小)値、cの個数)
T f(T a, T b, T c, int dis) { return a + (b - c) * dis; }
// dataに対する遅延伝搬(今回は除算を行うので長さは不要)
// 要素単体の更新は長さ１の区間の更新ととらえればいい。
T mapping(E a, T b, int len) { return b + a * len; }

E composition(E a, E b) { return a + b; }
E id() { return 0; }
R inf = 1e18;
struct Segment_Tree_Beats {
 private:
  int n{}, sz{}, height{};
  vector<T> data;
  // ノードの長さを表す配列
  vector<int> Len;

  // １番目・２番目(最大値)
  vector<R> max_v, smax_v;
  // １番目・２番目(最小値)
  vector<R> min_v, smin_v;
  // 最大値・最小値の個数
  vector<int> max_c, min_c;

  // 任意の遅延伝搬(単位元はid())
  vector<E> lazy;
  void update(int k) {
    data[k] = op(data[2 * k], data[2 * k + 1]);

    if (max_v[2 * k] > max_v[2 * k + 1]) {
      max_v[k] = max_v[2 * k];
      smax_v[k] = max(smax_v[2 * k], max_v[2 * k + 1]);
      max_c[k] = max_c[2 * k];
    } else if (max_v[2 * k] < max_v[2 * k + 1]) {
      max_v[k] = max_v[2 * k + 1];
      smax_v[k] = max(smax_v[2 * k + 1], max_v[2 * k]);
      max_c[k] = max_c[2 * k + 1];
    } else {
      max_v[k] = max_v[2 * k];
      smax_v[k] = max(smax_v[2 * k], smax_v[2 * k + 1]);
      max_c[k] = max_c[2 * k] + max_c[2 * k + 1];
    }
    if (min_v[2 * k] < min_v[2 * k + 1]) {
      min_v[k] = min_v[2 * k];
      smin_v[k] = min(smin_v[2 * k], min_v[2 * k + 1]);
      min_c[k] = min_c[2 * k];
    } else if (min_v[2 * k] > min_v[2 * k + 1]) {
      min_v[k] = min_v[2 * k + 1];
      smin_v[k] = min(smin_v[2 * k + 1], min_v[2 * k]);
      min_c[k] = min_c[2 * k + 1];
    } else {
      min_v[k] = min_v[2 * k];
      smin_v[k] = min(smin_v[2 * k], smin_v[2 * k + 1]);
      min_c[k] = min_c[2 * k] + min_c[2 * k + 1];
    }
  }

  void push(int k) {
    apply_push(k);
    max_push(k);
    min_push(k);
  }
  /*chminに用いる関数*/
  // 　最大値を親ノードから子ノードへの伝搬
  void max_push(int k) {
    if (max_v[k] < max_v[2 * k]) {
      push_min(2 * k, max_v[k]);
    }
    if (max_v[k] < max_v[2 * k + 1]) {
      push_min(2 * k + 1, max_v[k]);
    }
  }
  // chminによる関数の値の更新
  void push_min(int k, R x) {
    data[k] = f(data[k], x, max_v[k], max_c[k]);
    // 最小値も必要に応じて更新
    if (max_v[k] == min_v[k]) {
      max_v[k] = min_v[k] = x;
    } else if (max_v[k] == smin_v[k]) {
      max_v[k] = smin_v[k] = x;
    } else {
      max_v[k] = x;
    }
  }
  void max_all_apply(int k, R x) {
    // 更新する箇所が存在しないので終わり
    if (max_v[k] <= x) return;
    // 更新する箇所が一か所のみであるので更新して終わり
    else if (smax_v[k] < x) {
      push_min(k, x);
      return;
    }
    // 　今いる区間の全ての更新を追えたら子ノードに行って更新をし、ボトムアップで親ノードに更新する
    push(k);
    max_all_apply(2 * k, x);
    max_all_apply(2 * k + 1, x);
    update(k);
  }
  /*ここまで*/
  /*chmaxに用いる関数*/
  // 　最小値を親ノードから子ノードへの伝搬
  void min_push(int k) {
    if (min_v[k] > min_v[2 * k]) {
      push_max(2 * k, min_v[k]);
    }
    if (min_v[k] > min_v[2 * k + 1]) {
      push_max(2 * k + 1, min_v[k]);
    }
  }

  // 　xに対応して最小値とデータの値の更新
  void push_max(int k, R x) {
    data[k] = f(data[k], x, min_v[k], min_c[k]);
    if (min_v[k] == max_v[k]) {
      min_v[k] = max_v[k] = x;
    } else if (min_v[k] == smax_v[k]) {
      min_v[k] = smax_v[k] = x;
    } else {
      min_v[k] = x;
    }
  }

  void min_all_apply(int k, R x) {
    // 更新する箇所が存在しないので終わり
    if (x <= min_v[k]) return;
    // 更新する箇所が一か所のみであるので更新して終わり
    else if (x < smin_v[k]) {
      push_max(k, x);
      return;
    }
    // 　今いる区間の全ての更新を追えたら子ノードに行って更新をし、ボトムアップで親ノードに更新する
    push(k);
    min_all_apply(2 * k, x);
    min_all_apply(2 * k + 1, x);
    update(k);
  }
  /*ここまで*/

  void apply_push(int k) {
    if (lazy[k] != id()) {
      all_apply(2 * k, lazy[k]);
      all_apply(2 * k + 1, lazy[k]);
      lazy[k] = id();
    }
  }
  // 抽象遅延伝搬作業
  void all_apply(int k, E x) {
    max_v[k] = mapping(x, max_v[k], 1);
    if (smax_v[k] != -inf) smax_v[k] = mapping(x, smax_v[k], 1);
    min_v[k] = mapping(x, min_v[k], 1);
    if (smin_v[k] != inf) smin_v[k] = mapping(x, smin_v[k], 1);
    data[k] = mapping(x, data[k], Len[k]);
    lazy[k] = composition(x, lazy[k]);
  }

 public:
  Segment_Tree_Beats() = default;

  explicit Segment_Tree_Beats(int n) : Segment_Tree_Beats(vector<T>(n, e())) {}
  explicit Segment_Tree_Beats(const vector<T> &v) : n(v.size()) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    data = vector<T>(2 * sz, e());
    lazy = vector<E>(2 * sz, id());
    Len = vector<int>(2 * sz, 0);
    max_v.resize(2 * sz, -inf), min_v.resize(2 * sz, inf);
    smax_v.resize(2 * sz, -inf), smin_v.resize(2 * sz, inf);
    max_c.resize(2 * sz, 0), min_c.resize(2 * sz, 0);
    build(v);
  }

  void build(const vector<R> &v) {
    assert(n == (int)v.size());
    for (int k = 0; k < n; k++) {
      data[k + sz] = v[k];
      max_v[k + sz] = v[k], min_v[k + sz] = v[k];
      max_c[k + sz] = 1, min_c[k + sz] = 1;
      Len[k + sz] = 1;
    }
    for (int k = sz - 1; k > 0; k--)
      update(k), Len[k] = Len[2 * k] + Len[2 * k + 1];
  }

  void set(int k, const R x) {
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
  // i=l,...r-1においてmin(v[i],x)に更新
  void range_chmin(int l, int r, R x) {
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
      if (l & 1) max_all_apply(l++, x);
      if (r & 1) max_all_apply(--r, x);
    }
    l = l2, r = r2;

    // 更新する区間を部分的に含んだ区間においてボトムアップで子ノードに伝搬させながらdataの値を更新
    for (int i = 1; i <= height; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }
  // i=l,...r-1においてmax(v[i],x)に更新
  void range_chmax(int l, int r, R x) {
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
      if (l & 1) min_all_apply(l++, x);
      if (r & 1) min_all_apply(--r, x);
    }
    l = l2, r = r2;

    // 更新する区間を部分的に含んだ区間においてボトムアップで子ノードに伝搬させながらdataの値を更新
    for (int i = 1; i <= height; i++) {
      if (((l >> i) << i) != l) update(l >> i);
      if (((r >> i) << i) != r) update((r - 1) >> i);
    }
  }
  // i=l,...r-1においてv[i]=x
  void range_update(int l, int r, R x) {
    range_chmax(l, r, x), range_chmin(l, r, x);
  }
  // i=l,...r-1においてmapping(x,v[i])
  void range_apply(int l, int r, E x) {
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

  // max(A[l],A[l+1],...A[r-1])を求める
  R prod_max(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    if (l >= r) return e();
    l += sz;
    r += sz;
    // 更新する区間を部分的に含んだ区間においてトップダウンで子ノードに伝搬させながらdataの値を更新
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }
    T L = -inf, R = -inf;
    // 値をチェックする区間のdataの値をチェック
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = max(L, max_v[l++]);
      if (r & 1) R = max(max_v[--r], R);
    }
    return max(L, R);
  }
  // min(A[l],A[l+1],...A[r-1])を求める
  R prod_min(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    if (l >= r) return e();
    l += sz;
    r += sz;
    // 更新する区間を部分的に含んだ区間においてトップダウンで子ノードに伝搬させながらdataの値を更新
    for (int i = height; i > 0; i--) {
      if (((l >> i) << i) != l) push(l >> i);
      if (((r >> i) << i) != r) push((r - 1) >> i);
    }
    T L = inf, R = inf;
    // 値をチェックする区間のdataの値をチェック
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = min(L, min_v[l++]);
      if (r & 1) R = min(min_v[--r], R);
    }
    return min(L, R);
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
  // lに対しcheck(max(A[l],A[l+1],...A[r]))=trueとなる最大のrを返す
  template <typename C>
  int maximum_max_right(int l, const C check) {
    if (l >= n) return n;
    l += sz;
    for (int i = height; i > 0; i--) push(l >> i);
    R sum = -inf;
    do {
      while ((l & 1) == 0) l >>= 1;
      if (check(max(sum, max_v[l]))) {
        while (l < sz) {
          push(l);
          l <<= 1;
          auto nxt = max(sum, max_v[l]);
          if (not check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l + 1 - sz;
      }
      sum = max(sum, max_v[l++]);
    } while ((l & -l) != l);
    return n;
  }
  // rに対しcheck(max(A[l],A[l+1],...A[r]))=trueとなる最小のlを返す
  template <typename C>
  int maximum_min_left(int r, const C &check) {
    if (r <= 0) return 0;
    r += sz;
    for (int i = height; i > 0; i--) push((r - 1) >> i);
    R sum = -inf;
    do {
      r--;
      while (r > 1 and (r & 1)) r >>= 1;
      if (check(max(max_v[r], sum))) {
        while (r < sz) {
          push(r);
          r = (r << 1) + 1;
          auto nxt = max(max_v[r], sum);
          if (not check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = max(max_v[r], sum);
    } while ((r & -r) != r);
    return 0;
  }
  // lに対しcheck(min(A[l],A[l+1],...A[r-1]))=trueとなる最大のrを返す
  template <typename C>
  int minimum_max_right(int l, const C check) {
    if (l >= n) return n;
    l += sz;
    for (int i = height; i > 0; i--) push(l >> i);
    R sum = inf;
    do {
      while ((l & 1) == 0) l >>= 1;
      if (check(min(sum, min_v[l]))) {
        while (l < sz) {
          push(l);
          l <<= 1;
          auto nxt = min(sum, min_v[l]);
          if (not check(nxt)) {
            sum = nxt;
            l++;
          }
        }
        return l + 1 - sz;
      }
      sum = max(sum, min_v[l++]);
    } while ((l & -l) != l);
    return n;
  }
  // rに対しcheck(min(A[l],A[l+1],...A[r-1]))=trueとなる最小のlを返す
  template <typename C>
  int minimum_min_left(int r, const C &check) {
    if (r <= 0) return 0;
    r += sz;
    for (int i = height; i > 0; i--) push((r - 1) >> i);
    R sum = inf;
    do {
      r--;
      while (r > 1 and (r & 1)) r >>= 1;
      if (check(min(min_v[r], sum))) {
        while (r < sz) {
          push(r);
          r = (r << 1) + 1;
          auto nxt = min(min_v[r], sum);
          if (not check(nxt)) {
            sum = nxt;
            r--;
          }
        }
        return r - sz;
      }
      sum = min(min_v[r], sum);
    } while ((r & -r) != r);
    return 0;
  }
};

}  // namespace Segment_Tree_Beats_INVAl
using Segment_Tree_Beats_INVAl::Segment_Tree_Beats;
// set(k,x) A[k]=xに更新
// get(k,x) A[k]を返す
// prod(l,r) : op(A[l],A[l+1],...,A[r-1])を求める
// prod_min(l,r) : min(A[l],A[l+1],...,A[r-1])を求める
// prod_max(l,r) : max(A[l],A[l+1],...,A[r-1])を求める
// update_min(l,r,x) : i=l,...r-1においてA[i]=min(x,A[i])に更新
// update_max(l,r,x) : i=l,...r-1においてA[i]=max(x,A[i])に更新
// update_set(l,r,x) : i=l,...r-1においてA[i]=xに更新
// apply(l,r,x) : i=l,...r-1においてmappinf(x,A[i])を実行
// max_right(l,C) :
// lに対しcheck(op(A[l],A[l+1],...A[r]))=trueとなる最大のrを返す min_left(r, C)
// : rに対しcheck(op(A[l],A[l+1],...A[r]))=trueとなる最小のlを返す
// maximum_max_right(l,C) :
// lに対しcheck(max(A[l],A[l+1],...A[r]))=trueとなる最大のrを返す
// maximum_min_left(r, C) :
// rに対しcheck(max(A[l],A[l+1],...A[r]))=trueとなる最小のlを返す
// manimum_max_right(l,C) :
// lに対しcheck(min(A[l],A[l+1],...A[r]))=trueとなる最大のrを返す
// manimum_min_left(r, C) :
// rに対しcheck(min(A[l],A[l+1],...A[r]))=trueとなる最小のlを返す
// Sはdataを表している。
