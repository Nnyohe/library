#include <bits/stdc++.h>
using namespace std;
// 実装はUnion by sizeで行っている
class UnionFind {
 public:
  UnionFind() = default;

  /// @brief 重み付き Union-Find 木を構築します。
  /// @param n 要素数
  explicit UnionFind(size_t n) : m_parentsOrSize(n, -1), N(n) {}
  /// @brief 頂点 i の root のインデックスを返します。
  /// @param i 調べる頂点のインデックス
  /// @return 頂点 i の root のインデックス
  int leader(int i) {
    if (m_parentsOrSize[i] < 0) {
      return i;
    }
    const int root = leader(m_parentsOrSize[i]);
    // 経路圧縮
    return (m_parentsOrSize[i] = root);
  }

  /// @param w (b の重み) - (a の重み)
  /// a を含むグループと b を含むグループを併合する
  // グループが一致している場合何もしない
  void merge(int a, int b) {
    a = leader(a);
    b = leader(b);

    if (a != b) {
      // union by size (小さいほうが子になる）
      if (-m_parentsOrSize[a] < -m_parentsOrSize[b]) {
        std::swap(a, b);
      }
      m_parentsOrSize[a] += m_parentsOrSize[b];
      m_parentsOrSize[b] = a;
    }
  }

  /// @brief a と b が同じグループに属すかを返します。
  /// @param a 一方のインデックス
  /// @param b 他方のインデックス
  /// @return a と b が同じグループに属す場合 true, それ以外の場合は false
  /// a と b が同じグループに属すかを返す
  bool same(int a, int b) { return (leader(a) == leader(b)); }

  /// @brief i が属するグループの要素数を返します。
  /// @param i インデックス
  /// @return i が属するグループの要素数
  int size(int i) { return -m_parentsOrSize[leader(i)]; }
  vector<vector<int>> Groups() {
    vector<vector<int>> G;
    int sum = 0;
    vector<int> number(N, -1);
    for (int i = 0; i < N; i++) {
      int a = leader(i);
      if (number[a] == -1) {
        number[a] = sum;
        G.emplace_back(vector<int>{});
        G[sum].emplace_back(i);
        sum++;
      } else {
        G[number[i]].emplace_back(i);
      }
    }
    return G;
  }

 private:
  // m_parentsOrSize[i] は i の 親,
  // ただし root の場合は (-1 * そのグループに属する要素数)
  int N;
  std::vector<int> m_parentsOrSize;
};
int main() {
  int N, t;
  cin >> N >> t;
  UnionFind d(N);
  while (t--) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a == 0) d.merge(c, b);
    else
      cout << d.same(b, c) << endl;
  }
}