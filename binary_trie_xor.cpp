/* binary_trie
insert(x,w): xをw個追加する。
insert(x,w): xを1個追加する。
erase(x,w): xをw個削除する。
erase(x): xを全て削除する。
search(x):xを個数を調べる
count(): binary_trieにある数字の個数。
at(k): binary_trieのk(0-index)番目に小さい要素の数
count_ress_eq(x): x以下の要素の個数
count_ress(x): x未満の要素の個数
count_upper_eq(x): x以上の要素の個数
count_upper(x): xより大きい要素の個数
erement_ress_eq(x): x以下の要素のうち最大の要素を出力
erement_ress(x): x未満の要素のうち最大の要素を出力
erament_upper_eq(x): x以上の要素のうち最小の要素の出力
eremant_upper(x): xより大きいx以下の要素のうち最大の要素を出力
*/

#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct binary_trie {
  struct Node {               // 頂点を表す構造体
    std::array<int, 2> next;  // 子の頂点番号を格納。存在しなければ-1
    long long common;         // いくつの単語がこの頂点を共有しているか
    Node() : common(0) { next.fill(-1); };
  };
  // (2^depthまでの桁をみる)
  vector<Node> nodes;  // trie 木本体
  T Xor = 0;
  int root;
  int depth = 60;
  binary_trie() : root(0) { nodes.push_back(Node()); }
  binary_trie(int dep) : root(0), depth(dep) { nodes.push_back(Node()); }
  // 任意の数の数字を追加する
  void insert(const T &word, long long number) {
    int node_id = 0;
    for (int i = depth; i > -1; i--) {
      int c = (word >> i) & 1;

      // cout << next_id << ' ' << node_id <<' '<<nodes[node_id].next.size() <<'
      // ' <<c << endl;
      if (nodes[node_id].next.at(c) == -1) {  // 次の頂点が存在しなければ追加
        nodes[node_id].next.at(c) = (int)nodes.size();
        nodes.emplace_back(Node());
      }
      nodes[node_id].common += number;
      node_id = nodes[node_id].next.at(c);
      ;
    }
    nodes[node_id].common += number;
  }
  // 数を１個追加する
  void insert(const T &word) { insert(word, 1); }
  // 削除処理：number個存在するなら削除して、そうでない場合は何もしない)
  void erase(const T &word, long long number) {
    if (number == 0) return;
    int node_id = 0;
    stack<int> S;
    for (int i = depth; i > -1; i--) {
      nodes[node_id].common -= number;
      int c = (word >> i) & 1;
      if (nodes[node_id].next.at(c) == -1) {  // 次の頂点が存在しなければ修了
        return;
      }
      node_id = nodes[node_id].next.at(c);
    }
    nodes[node_id].common -= number;
  }
  // wordの要素を全削除
  void erase(const T &word) { return erase(word, search(word)); }

  // 数字の個数の検索
  long long search(const T word) {
    int node_id = 0;
    word ^= Xor;
    for (int i = depth; i > -1; i--) {
      int c = (word >> i) & 1;
      if (nodes[node_id].next[c] == -1) {  // 次の頂点が存在しなければ終了
        return 0;
      }
      node_id = nodes[node_id].next[c];
    }
    // 0個のノードも存在する
    return nodes[node_id].common;
  }

  // binary_trieに存在する要素の個数
  int count() { return nodes[0].common; }
  // binary_trieに存在する要素の最大値(要素自体が無ければ-1を出力)
  T maximum() {
    long long sum = 0;
    if (nodes[0].common == 0) return -1;
    int node_id = 0;
    for (int i = depth; i > -1; i--) {
      int next_id = nodes[node_id].next.at((((Xor >> i) & 1) ^ 1));
      // 1<<iを加える道について次が存在するかつ、そこに属する要素が存在する場合
      if (next_id != -1 && nodes[next_id].common > 0) {
        sum += (1LL << i);
        node_id = next_id;
      }
      // そうでない場合、仕方ないので1<<iを加えないで次に行く
      else {
        node_id = nodes[node_id].next.at(((Xor >> i) & 1));
      }
    }
    return sum;
  }
  // binary_trieに存在する要素の最小値(要素自体が無ければ-1を出力)
  T minimum() {
    T sum = 0;
    if (nodes[0].common == 0) return -1;
    int node_id = 0;
    for (int i = depth; i > -1; i--) {
      int next_id = nodes[node_id].next.at(((Xor >> i) & 1));
      // 1<<iを加えない道について次が存在するかつ、そこに属する要素が存在する場合
      if (next_id != -1 && nodes[next_id].common > 0) {
        node_id = next_id;
      }
      // そうでない場合仕方ないので1<<iを加え次に行く
      else {
        sum += (1LL << i);
        node_id = nodes[node_id].next.at((((Xor >> i) & 1) ^ 1));
      }
    }
    return sum;
  }
  // binary_trieの小さい順からk(0-index)番目の要素(要素自体が無ければ-1を出力)
  T at(int k) {
    // 範囲外参照した場合-1を出力する。
    if (k < 0 || k >= count()) {
      return -1;
    }
    int x = k;
    T sum = 0;
    int node_id = 0;
    for (int i = depth; i > -1; i--) {
      T c = ((Xor >> i) & 1);
      int next_id = nodes[node_id].next[c];
      if (next_id != -1) {
        if (nodes[next_id].common > x) {
          node_id = next_id;
        } else {
          sum += (1LL << i);
          node_id = nodes[node_id].next[1 ^ c];
          x -= nodes[next_id].common;
        }
      } else {
        sum += (1LL << i);
        node_id = nodes[node_id].next[1 ^ c];
      }
      if (node_id == -1) break;
    }
    return sum;
  }
  // word以下の要素の数
  int count_ress_eq(T word) {
    int sum = 0;
    int node_id = 0;

    for (int i = depth; i > -1; i--) {
      T c = ((Xor >> i) & 1) ^ 1;
      int next_id = nodes[node_id].next[c ^ 1];
      // wordのi桁目が1のビットのとき操作を終えた後、i桁目が1であるものに移動する。
      if ((word >> i) & 1 == c) {
        //  i桁目が0の場合、明らかに下回るのでその個数を追加する。
        if (next_id != -1) sum += nodes[next_id].common;
        node_id = nodes[node_id].next[c];

      }
      // それ意外の場合、i桁目が0であるものに移動する。
      else
        node_id = next_id;
      if (node_id == -1) {
        break;
      }
    }
    // word に等しくなる要素の個数の追加
    if (node_id != -1) sum += nodes[node_id].common;
    return sum;
  }
  // word未満の要素の数
  int count_ress(T word) {
    int sum = 0;
    int node_id = 0;

    for (int i = depth; i > -1; i--) {
      T c = ((Xor >> i) & 1) ^ 1;
      int next_id = nodes[node_id].next[c ^ 1];
      // wordのi桁目が1のビットのとき操作を終えた後、i桁目が1であるものに移動する。
      if ((word >> i) & 1 == c) {
        //  i桁目が0の場合、明らかに下回るのでその個数を追加する。
        if (next_id != -1) sum += nodes[next_id].common;
        node_id = nodes[node_id].next[c];

      }
      // それ意外の場合、i桁目が0であるものに移動する。
      else
        node_id = next_id;
      if (node_id == -1) {
        break;
      }
    }
    return sum;
  }
  // word以上の要素の数
  int count_upper_eq(const T &word) { return (count() - count_ress(word)); }
  // wordよりも大きい要素の数
  int count_upper(const T &word) { return count() - count_ress_eq(word); }
  // wordよりも小さい要素の中で最大の要素を出力
  T erement_ress(const T &word) { return at(count_ress(word) - 1); }
  // word以下の要素の中で最大の要素を出力
  T erement_ress_eq(const T &word) { return at(count_ress_eq(word) - 1); }
  // word以上の要素の中で最小の要素を出力
  T erement_upper_eq(const T &word) { return at(count_ress(word)); }
  // wordよりも大きい要素の中で最小の要素を出力
  T erement_upper(T word) { return at(count_ress_eq(word + 1)); }
  void XOR(T word) { Xor ^= word; }
};
int main() {
  int t;
  cin >> t;
  binary_trie<int> A(31);
  for (int i = 0; i < t; i++) {
    int a, b;
    cin >> a >> b;
    //  cout << A.count() << endl;
    if (a == 0) {
      if (A.search(a)) continue;
      A.insert(b);
    } else if (a == 1) {
      A.erase(b);
    } else {
      A.XOR(b);
      cout << A.minimum() << endl;
      A.XOR(b);
    }
  }
}