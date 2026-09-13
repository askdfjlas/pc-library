#ifndef COMB_HPP
#define COMB_HPP

#include "starter.hpp"
#include "utilities/math.hpp"

template<class T> struct Comb {
  int max_n;
  vector<T> fact_, fact_inv_;
  Comb(int max_n_): max_n(max_n_) {}
  void _load_facts_if_needed() {
    if(!fact_.empty()) [[likely]] return;
    fact_.resize(max_n + 1);
    fact_[0] = 1;
    FORR(i,1,max_n)
      fact_[i] = fact_[i - 1] * i;
  }
  void _load_fact_invs_if_needed() {
    if(!fact_inv_.empty()) [[likely]] return;
    _load_facts_if_needed();
    fact_inv_.resize(max_n + 1);
    FORR(i,0,max_n)
      fact_inv_[i] = T{1}/fact_[i];
  }
  T fact(int n) {
    _load_facts_if_needed();
    return fact_[n];
  }
  T fact_inv(int n) {
    _load_fact_invs_if_needed();
    return fact_inv_[n];
  }
  T choose(int n, int k) {
    _load_fact_invs_if_needed();
    if(k > n) return 0;
    return fact_[n] * fact_inv_[k] * fact_inv_[n - k];
  }
};

#endif