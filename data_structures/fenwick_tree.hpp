#ifndef FENWICK_TREE_HPP
#define FENWICK_TREE_HPP

#include "starter.hpp"

template <typename T> struct FenwickTree {
  int n, high_bit;
  vector<T> tree;
  FenwickTree(int n_) : n(n_) {
    tree.resize(n + 1);
    high_bit = 1;
    while((high_bit << 1) <= n) high_bit <<= 1;
  }
  FenwickTree(const vector<T>& a) : FenwickTree((int)a.size()) {
    FORR(i,1,n) {
      tree[i] += a[i];
      int r = i + (i & -i);
      if(r <= n) tree[r] += tree[i];
    }
  }
  int size() { return n; }
  int lower_bound(T x) {
    int res = 0; T cur = 0;
    for(int bit = high_bit; bit > 0; bit >>= 1) {
      if((res|bit) <= n && cur + tree[res|bit] < x) {
        res |= bit; cur += tree[res];
      }
    }
    return res;
  }
  T prefix_sum(int i) {
    T ret = 0;
    for(i++; i > 0; i -= (i & -i)) ret += tree[i];
    return ret;
  }
  T range_sum(int l, int r) { return l > r ? 0 : prefix_sum(r) - prefix_sum(l - 1); }
  void update(int i, T delta) { for(i++; i <= n; i += (i & -i)) tree[i] += delta; }
  void set(int i, T x) { update(i, x - range_sum(i, i)); }
};

#endif
