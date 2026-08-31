#ifndef POINT_SEGMENT_TREE_HPP
#define POINT_SEGMENT_TREE_HPP

#include "starter.hpp"

template <class T> struct PointSegmentTree {
  int size = 1, n;
  vector<T> tree;
  PointSegmentTree(int n_) : PointSegmentTree(vector<T>(n_)) {}
  PointSegmentTree(const vector<T>& arr) : n((int)arr.size()) {
    while(size < (int)arr.size())
      size <<= 1;
    tree = vector<T>(size << 1);
    for(int i = size + arr.size() - 1; i >= 1; i--)
      if(i >= size) tree[i] = arr[i - size];
      else _consume(i);
  }
  void set(int i, T val) {
    tree[i += size] = val;
    for(i >>= 1; i >= 1; i >>= 1)
      _consume(i); 
  }
  void update(int i, T val) { set(i, tree[i + size] * val); }
  T get(int i) { return tree[i + size]; }
  T query(int l, int r) {
    if(l == r + 1) return T();
    T resl, resr;
    for(l += size, r += size + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) resl = resl * tree[l++];
      if(r & 1) resr = tree[--r] * resr;
    }
    return resl * resr;
  }
  T query_all() { return tree[1]; }
  int first_true(int l, function<bool(T)> f) {
    if(l == n) return n;
    assert(!f(T()));
    l += size;
    T sm;
    do {
      while(!(l & 1)) l >>= 1;
      if(f(sm * tree[l])) {
        while(l < size) {
          l <<= 1;
          if(!f(sm * tree[l])) {
            sm = sm * tree[l];
            l++;
          }
        }
        return l - size;
      }
      sm = sm * tree[l];
      l++;
    } while((l & -l) != l); 
    return n;
  }
  void _consume(int i) { tree[i] = tree[i << 1] * tree[i << 1 | 1]; }
};

#endif
