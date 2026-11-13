#ifndef MATH_HPP
#define MATH_HPP

#include "starter.hpp"

namespace math {
  constexpr bool is_known_prime(ll n) {
    return n == 998244353 || n == (1e9 + 7);
  }
  
  ll mod_pow(ll x, ll y, ll mod) {
    ll res = 1;
    while(y > 0) {
      if(y & 1) res = (res * x) % mod;
      y >>= 1;
      x = (x * x) % mod;
    }
    return res;
  }
  
  /*
  For x, y >= 0, returns [g, a, b] such that g = gcd(x, y), and ax + by = g
  max(g, |a|, |b|) <= max(x, y, 1) and it can't overflow
  */
  template <typename T>
  tuple<T, T, T> extended_gcd(T x, T y) {
    if(x == 0) return {y, T(0), T(1)};
    T k = y/x;
    auto [g, a, b] = extended_gcd(y - k * x, x);
    return {g, b - a * k, a};
  }
  
  template <typename T>
  T mod_inv(T x, T mod) {
    // I have no idea which is faster (in fact both branches could be written faster) but I'll copy Atcoder anyways
    if(is_known_prime(mod))
      return mod_pow(x, mod - 2, mod);
    else {
      auto [g, a, b] = extended_gcd(x, mod);
      return (a + mod) % mod;
    }
  }
}

#endif
