#ifndef PRF_HPP
#define PRF_HPP

#include "starter.hpp"

ll _h(ll x) { return x * x * x * 1241483 + 19278349; }
ll prf(ll x) { return _h(x & ((1 << 31) - 1)) + _h(x >> 31); }

#endif