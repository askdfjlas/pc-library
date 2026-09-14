#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include "starter.hpp"

struct Permutation {
  vector<int> p;
  Permutation(int n_) {
    p.resize(n_);
    FORR(i,1,n_) p[i - 1] = i;
  }
  Permutation(vector<int> p_): p(p_) {}
  int& operator[](int i) { return p[i - 1]; }
  const int& operator[](int i) const { return p[i - 1]; }
  size_t size() const { return p.size(); }
  Permutation inv() const {
    int n = p.size();
    Permutation res(n);
    FORR(i,1,n) res[p[i]] = i;
    return res;
  }
  friend ostream& operator<<(ostream& os, const Permutation rhs) {
    int n = rhs.size();
    FORR(i,1,n) {
      os << rhs[i];
      if(i < n) os << ' ';
    }
    return os;
  }
  friend istream& operator>>(istream& is, Permutation& rhs) {
    int n = rhs.size();
    FORR(i,1,n) is >> rhs[i];
    return is;
  }
};

#endif