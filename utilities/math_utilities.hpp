#ifndef MATH_UTILITIES_HPP
#define MATH_UTILITIES_HPP

#include "starter.hpp"

namespace math_utilities {
  ll pow_mod(ll x, ll y, ll mod) {
    ll res = 1;
    while(y > 0) {
      if(y & 1) res = (res * x) % mod;
      y >>= 1;
      x = (x * x) % mod;
    }
    return res;
  }
  
  pair<ll,pair<ll,ll>> extended_gcd(ll a, ll b) {
    if(a == 0) return {b, {0ll, 1ll}};
    ll k = b/a;
    auto [g, sol] = extended_gcd(b - k * a, a);
    auto [c, d] = sol;
    return {g, {d - c * k, c}};
  }
}

#endif
