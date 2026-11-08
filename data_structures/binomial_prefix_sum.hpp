#ifndef BINOMIAL_PREFIX_SUM_HPP
#define BINOMIAL_PREFIX_SUM_HPP

#include "data_structures/comb.hpp"
#include "starter.hpp"

template <class T> struct BinomialPrefixSum {
  int n = 0, k = 0;
  T x = 1;
  Comb<T>& comb;
  BinomialPrefixSum(Comb<T>& comb_) : comb(comb_) {}
  void increment_n() {
    x = 2 * x - comb.choose(n, k); 
    n++;
  }
  void decrement_n() {
    assert(n > k);
    n--;
    x = (x + comb.choose(n, k))/2;
  }
  void increment_k() {
    assert(k < n);
    k++;
    x += comb.choose(n, k);
  }
  void decrement_k() {
    assert(k > 0);
    x -= comb.choose(n, k);
    k--;
  }
  T get() { return x; }
  void set(int n_, int k_) {
    while(n < n_) increment_n();
    while(k < k_) increment_k();
    while(k > k_) decrement_k();
    while(n > n_) decrement_n();
  }
};

#endif
