#ifndef BIT_UTILITIES_HPP
#define BIT_UTILITIES_HPP

namespace bit_utilities {
  inline int count_trailing_zeroes(int n) {
    return __builtin_ctz(n);
  }

  inline int count_leading_zeroes(int n) {
    return __builtin_clz(n);
  }

  inline int high_bit_index(int n) {
    return 31 - count_leading_zeroes(n);
  }

  inline int high_bit(int n) {
    return 1 << high_bit_index(n);
  }

  inline int count_trailing_zeroes(ll n) {
    return __builtin_ctzll(n);
  }

  inline int count_leading_zeroes(ll n) {
    return __builtin_clzll(n);
  }

  inline int high_bit_index(ll n) {
    return 63 - count_leading_zeroes(n);
  }

  inline ll high_bit(ll n) {
    return 1ll << high_bit_index(n);
  }
}

#endif
