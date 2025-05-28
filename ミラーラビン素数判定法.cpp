#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
__int128_t Power(__int128_t a, __int128_t b, __int128_t m) {
  __int128_t p = a, Answer = 1;
  for (int i = 0; i < 63; i++) {
    __int128_t wari = (1LL << i);
    if ((b / wari) % 2 == 1) {
      Answer %= m;
      Answer = (Answer * p) % m;  // 「a の 2^i 乗」が掛けられるとき
    }
    p %= m;
    p = (p * p) % m;
  }
  return Answer;
}
// ミラーラビン素数判定法(10**18以下の素数までなら判定可能)
bool is_prime(long long N) {
  if (N <= 1) return false;
  if (N == 2 || N == 3) return true;
  if (N % 2 == 0) return false;
  vector<long long> A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  long long s = 0, d = N - 1;
  while (d % 2 == 0) {
    ++s;
    d >>= 1;
  }
  for (auto a : A) {
    if (a % N == 0) return true;
    long long t, x = Power(a, d, N);
    if (x != 1) {
      for (t = 0; t < s; ++t) {
        if (x == N - 1) break;
        x = __int128_t(x) * x % N;
      }
      if (t == s) return false;
    }
  }
  return true;
}