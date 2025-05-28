/*
merge sort tree
特徴１：配列は静的である(クエリごとに配列の値が変化することは無い)ことが条件である。
特徴②：空間O(NlonN),１クエリO((logN)^2)
特徴3：区間においてある閾値以上・以下・未満における何かしらの値を求めたい場合に使う（デフォは個数)
*/
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct merge_sort_tree {
 private:
  int n{}, sz{}, height{};
  vector<vector<T>> node;
  vector<vector<T>> SUM;
  vector<T> combine(vector<T> &l, vector<T> &r) {
    int l1 = 0;
    int r1 = 0;

    vector<T> newx = {};
    while (l1 < (int)l.size() || r1 < (int)r.size()) {
      if (l1 == l.size())
        newx.emplace_back(r[r1++]);
      else if (r1 == r.size())
        newx.emplace_back(l[l1++]);
      else {
        if (r[r1] < l[l1])
          newx.emplace_back(r[r1++]);
        else
          newx.emplace_back(l[l1++]);
      }
    }
    return newx;
  };
  void update(int k) { node[k] = combine(node[2 * k], node[2 * k + 1]); }

 public:
  merge_sort_tree(vector<T> &A) : n((int)A.size()) {
    sz = 1;
    height = 0;
    while (sz < n) sz <<= 1, height++;
    node = vector<vector<T>>(2 * sz);
    SUM = vector<vector<T>>(2 * sz);
    for (int i = 0; i < (int)A.size(); i++) {
      node[sz + i].emplace_back(A[i]);
    }

    for (int i = sz - 1; i > 0; --i) {
    
      update(i);
    }

    for (int i = 1; i < 2 * sz; i++) {
      SUM[i].emplace_back(0);
      for (int j = 0; j < node[i].size(); j++) {
        SUM[i].emplace_back(node[i][j] + SUM[i].back());
      }
    }
  }
  T get(int k) { return node[k + sz]; }
  T operator[](int i) {
    assert(0 <= i && i < n);
    return node[i + sz][0];
  }
  // 右側を基準にして、条件式を満たす数列の個数を数える場合(~以上など)(具体的には
  // check(node[k][x]))=trueならばy>xにおいてcheck(node[k][y]))=trueが保証されている。
  template <typename C>
  T max_right(int k, const C &check) {
    int l = 0, r = node[k].size() + 1;
    while (r - l > 1) {
      int mid = midpoint(l, r);
      if (check(node[k][mid - 1]))
        l = mid;
      else
        r = mid;
    }
    return  SUM[k][l];
  }
  // 右側を基準にして、条件式を満たす数列の個数を数える場合(~以下など)(具体的には
  // check(node[k][x]))=trueならばy<xにおいてcheck(node[k][y]))=trueが保証されている。
  template <typename C>
  T min_left(int k, const C &check) {
    int l = 0, r = node[k].size() + 1;
    while (r - l > 1) {
      int mid = midpoint(l, r);
      if (check(node[k][node[k].size() - mid]))
        l = mid;
      else
        r = mid;
    }
    return SUM[k][l];
  }
  // 以下とか未満の場合の個数を数える場合に使う。
  template <typename C>
  T Less_prod(int l, int r, const C &check) {
    assert(0 <= l && l <= r && r <= n);

    T sum = 0;
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      // 区間内のものを左右から結合
      if (l & 1) sum += max_right(l++, check);
      if (r & 1) sum += max_right(--r, check);
    }
    return sum;
  }
  // 以上とかより大きいの場合の個数を数える場合に使う。
  template <typename C>
  T More_prod(int l, int r, const C &check) {
    assert(0 <= l && l <= r && r <= n);
    T res = identity();  // 初期値は単位元
    T res2 = identity();
    int sum = 0;
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      // 区間内のものを左右から結合
      if (l & 1) sum += min_left(l++, check);
      if (r & 1) sum += min_left(--r, check);
    }
    return sum;
  }
  // q未満を満たす集合に関する何かを行う。(個数なり、総和なり)
  T CntLess(int l, int r, T q) {
    auto check = [&](T v) -> bool { return v < q; };
    return Less_prod(l, r, check);
  }
  // q以下を満たす集合に関する何かを行う。
  T CntLess_and_eq(int l, int r, T q) {
    auto check = [&](T v) -> bool { return v <= q; };
    return Less_prod(l, r, check);
  }
    // qを超える集合に関する何かを行う。
  T CntMore(int l, int r, T q) {
    auto check = [&](T v) -> bool { return v > q; };
    return More_prod(l, r, check);
  }  // q以上を満たす集合に関する何かを行う。
  T CntMore_and_eq(int l, int r, T q) {
    auto check = [&](T v) -> bool { return v >= q; };
    return More_prod(l, r, check);
  }
};

int main() {
  int N, t;
  cin >> N;
  vector<long long> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  merge_sort_tree seg(A);
  cin >> t;
  long long a, b, c, d=0;
  while (t--) {
    cin >> a >> b >> c;
    a ^= d, b ^= d, c ^= d;
    --a;
    d = seg.CntLess_and_eq(a, b, c);
    cout << d << endl;
  }
}
