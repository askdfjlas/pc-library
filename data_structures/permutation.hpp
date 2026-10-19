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
  int size() const { return (int)p.size(); }
  Permutation operator*(const Permutation& rhs) const {
    int n = size();
    assert(rhs.size() == n);
    vector<int> res(n);
    FORR(i,1,n) res[i - 1] = (*this)[rhs[i]];
    return Permutation(res);
  }
  Permutation inv() const {
    int n = p.size();
    vector<int> res(n);
    FORR(i,1,n) res[(*this)[i] - 1] = i;
    return Permutation(res);
  }
  Permutation shuffle(const Permutation& q) const { return (operator*)(q); }
  vector<vector<int>> cycles() const {
    int n = size();
    vector<vector<int>> res;
    vector<bool> vis(n);
    FORR(i,1,n) {
      if(vis[i - 1]) continue;
      vector<int> cur_cycle;
      int cur = i;
      while(!vis[cur - 1]) {
        vis[cur - 1] = true;
        cur_cycle.push_back(cur);
        cur = (*this)[cur];
      }
      res.push_back(cur_cycle);
    }
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