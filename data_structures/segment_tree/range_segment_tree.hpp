#ifndef RANGE_SEGMENT_TREE_HPP
#define RANGE_SEGMENT_TREE_HPP

#include "starter.hpp"

template <class T, class F> struct RangeSegmentTree {
  int size = 1, log = 0;
  vector<T> tree;
  vector<F> lazy;
  RangeSegmentTree(int n_) : RangeSegmentTree(vector<T>(n_)) {}
  RangeSegmentTree(const vector<T>& arr) {
    while(size < (int)arr.size()) {
      size <<= 1;
      log++;
    }
    tree = vector<T>(size << 1);
    lazy = vector<F>(size);
    for(int i = size + arr.size() - 1; i >= 1; i--)
      if(i >= size) tree[i] = arr[i - size];
      else _consume(i);
  }
  void set(int i, T val) {
    i += size;
    _flush_to_leaf(i);
    tree[i] = val;
    _consume_to_root(i);
  }
  T get(int i) {
    i += size;
    _flush_to_leaf(i);
    return tree[i];
  }
  T query(int l, int r) {
    if(l == r + 1) return T();
    l += size; 
    r += size + 1;
    for(int i = log; i >= 1; i--) {
      if(((l >> i) << i) != l) _flush(l >> i); 
      if(((r >> i) << i) != r) _flush((r - 1) >> i);
    }
    T resl, resr;
    for(; l < r; l >>= 1, r >>= 1) {
      if(l & 1) resl = resl * tree[l++];
      if(r & 1) resr = tree[--r] * resr;
    }
    return resl * resr;
  }
  T query_all() { return tree[1]; }
  void update(int i, F f) {
    i += size;
    _flush_to_leaf(i);
    tree[i] = f * tree[i];
    _consume_to_root(i);
  }
  void update(int l, int r, F f) {
    if(l == r + 1) return;
    l += size;
    r += size + 1;
    for(int i = log; i >= 1; i--) {
      if(((l >> i) << i) != l) _flush(l >> i); 
      if(((r >> i) << i) != r) _flush((r - 1) >> i);
    }
    for(int l2 = l, r2 = r; l2 < r2; l2 >>= 1, r2 >>= 1) {
      if(l2 & 1) _apply(l2++, f);
      if(r2 & 1) _apply(--r2, f);
    }
    for(int i = 1; i <= log; i++) {
      if(((l >> i) << i) != l) _consume(l >> i); 
      if(((r >> i) << i) != r) _consume((r - 1) >> i);
    }
  }
  void _apply(int i, F f) {
    tree[i] = f * tree[i];
    if(i < size) lazy[i] = f * lazy[i];
  }
  void _consume(int i) { tree[i] = tree[i << 1] * tree[i << 1 | 1]; }
  void _consume_to_root(int i) { for(i >>= 1; i >= 1; i >>= 1) _consume(i); }
  void _flush(int i) { _apply(i << 1, lazy[i]); _apply(i << 1 | 1, lazy[i]); lazy[i] = F(); }
  void _flush_to_leaf(int i) { for(int j = log; j >= 1; j--) _flush(i >> j); }
};

#endif
