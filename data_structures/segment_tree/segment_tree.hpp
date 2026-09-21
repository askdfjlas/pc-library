#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include "starter.hpp"

template <class T, T (*op)(T, T), T one> struct SegmentTree {
  int size = 1, n;
  vector<T> tree;
  SegmentTree(int n_) : SegmentTree(vector<T>(n_)) {}
  SegmentTree(const vector<T>& a) : n((int)a.size()) {
    while(size < (int)a.size())
      size <<= 1;
    tree = vector<T>(size << 1, one);
    for(int i = size + a.size() - 1; i >= 1; i--)
      if(i >= size) tree[i] = a[i - size];
      else _consume(i);
  }
  T get(int i) { return tree[i + size]; }
  void set(int i, T x) {
    tree[i += size] = x;
    for(i >>= 1; i >= 1; i >>= 1)
      _consume(i); 
  }
  void update(int i, T x) { set(i, op(get(i), x)); }
  T prod(int l, int r) {
    assert(0 <= l && l <= r + 1 && r < n);
    if(l == r + 1) return one;
    T pl = one, pr = one;
    for(l += size, r += size + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) pl = op(pl, tree[l++]);
      if(r & 1) pr = op(tree[--r], pr);
    }
    return op(pl, pr);
  }
  T total_prod() { return tree[1]; }
  int first_true_from_left(function<bool(T)> f, int l = 0) {
    assert(!f(one));
    assert(0 <= l && l <= n);
    if(l == n) return n;
    l += size;
    T p = one;
    do {
      while(!(l & 1)) l >>= 1;
      if(f(op(p, tree[l]))) {
        while(l < size) {
          l <<= 1;
          if(!f(op(p, tree[l]))) {
            p = op(p, tree[l]);
            l++;
          }
        }
        return l - size;
      }
      p = op(p, tree[l]);
      l++;
    } while((l & -l) != l); 
    return n;
  }
  int first_true_from_right(function<bool(T)> f, optional<int> r = nullopt) {
    assert(!f(one));
    int _r = r.value_or(n - 1);
    assert(-1 <= _r && _r < n);
    if(_r == -1) return -1;
    _r += size;
    T p = one;
    do {
      while(_r > 1 && _r & 1) _r >>= 1;
      if(f(op(tree[_r], p))) {
        while(_r < size) {
          _r = (_r << 1) | 1;
          if(!f(op(tree[_r], p))) {
            p = op(tree[_r], p);
            _r--;
          }
        }
        return _r - size;
      }
      p = op(tree[_r], p);
      _r--;
    } while(((_r + 1) & -(_r + 1)) != _r + 1);
    return -1;
  }
  void _consume(int i) { tree[i] = op(tree[i << 1], tree[i << 1 | 1]); }
};

#endif
