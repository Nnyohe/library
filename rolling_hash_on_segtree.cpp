#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll = long long;
#define reps(i, a, n) for (ll i = (a); i < (ll)(n); i++)
#define rep(i, n) for (ll i = (0); i < (ll)(n); i++)
namespace rolling_hash_on_segtree_INVAl {
struct Sx {
  __int128_t value;  // 値
  __int128_t
      x;  // 乱択で選ばれた数をHASHとすると右側にいくつHASYがあるか(説明が難しい)
  __int128_t mod;  // modはmod
                   // 値更新型の遅延セグ木を作りたければ長さを追加する必要もある
};
Sx op(Sx a, Sx b) {
  return {((a.value * b.x) % a.mod + b.value) % a.mod, (a.x * b.x) % a.mod,
          a.mod};
}
// １つ目のmodに対応した単位元
Sx e() { return {0, 1, (1LL << 61) - 1}; }

// 2つ目のmodに対応した単位元
Sx e2() { return {0, 1, 1000000007}; }
// 念のため２つ用意してある(1つで十分だと思う...)
vector<__int128_t> MOD = {(1LL << 61) - 1, 1000000007};
segtree<Sx, op, e> segS, segT;
segtree<Sx, op, e2> segS1, segT1;

__int128_t a = randomINT(2, (1LL << 61) - 2);
__int128_t b = randomINT(2, 1000000006);

vector<__int128_t> HASH = {a, b};

// 参考(https://nyaannyaan.github.io/library/string/rolling-hash-on-segment-tree.hpp.html)
struct rolling_hash_on_segtree {
 private:
  int n{};
  vector<__int128_t> A, B;

 public:
  rolling_hash_on_segtree() = default;
  explicit rolling_hash_on_segtree(int n, vector<__int128_t> A,
                                   vector<__int128_t> B)
      : n(n), A(A), B(B) {
    build(n, A, B);
  };
  explicit rolling_hash_on_segtree(vector<__int128_t> A, vector<__int128_t> B)
      : rolling_hash_on_segtree(A.size(), A, B) {};
  void build(int n, vector<__int128_t> &A, vector<__int128_t> &B) {
    segtree<Sx, op, e> r(n);
    segS = r;
    segT = r;
    rep(i, A.size()) segS.set(i, {A[i], a, MOD[0]});
    rep(i, B.size()) segT.set(i, {B[i], a, MOD[0]});
    segtree<Sx, op, e2> r2(n);
    segS1 = r2;
    segT1 = r2;
    rep(i, A.size()) segS1.set(i, {A[i], b, MOD[1]});
    rep(i, B.size()) segT1.set(i, {B[i], b, MOD[1]});
    return;
  }
  // １番目のk番目の要素をkに変更する
  void setS(int k, __int128_t x) {
    segS.set(k, {x, HASH[0], MOD[0]}), segS1.set(k, {x, HASH[1], MOD[1]});
  }
  // 2番目のk番目の要素をkに変更する
  void setT(int k, __int128_t x) {
    segT.set(k, {x, HASH[0], MOD[0]}), segT1.set(k, {x, HASH[1], MOD[1]});
  }

  // i∈[l,r)を満たす１番目の文字列のハッシュ値
  vector<__int128_t> prodS(int l, int r) {
    return {segS.prod(l, r).value, segS1.prod(l, r).value};
  }
  // i∈[l,r)を満たす2番目の文字列のハッシュ値
  vector<__int128_t> prodT(int l, int r) {
    return {segT.prod(l, r).value, segT1.prod(l, r).value};
  }
  // i∈[0,n)を満たす１番目の文字列のハッシュ値
  vector<__int128_t> all_prodS() {
    return {segS.all_prod().value, segS1.all_prod().value};
  }
  // i∈[0,n)を満たす2番目の文字列のハッシュ値
  vector<__int128_t> all_prodT() {
    return {segT.all_prod().value, segT1.all_prod().value};
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

}  // namespace rolling_hash_on_segtree_INVAl
   // namespace rolling_hash_on_segtree_INVAl
using rolling_hash_on_segtree_INVAl::rolling_hash_on_segtree;