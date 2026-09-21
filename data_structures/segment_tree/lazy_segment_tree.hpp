#ifndef LAZY_SEGMENT_TREE_HPP
#define LAZY_SEGMENT_TREE_HPP

#include "starter.hpp"

template <
  class T,
  T (*op)(T, T),
  T one,
  class F,
  T (*apply_)(F, T),
  F (*compose)(F, F),
  F identity
>
struct LazySegmentTree {
  int size = 1, log = 0, n;
  vector<T> tree;
  vector<F> lazy;
  LazySegmentTree(int n_) : LazySegmentTree(vector<T>(n_)) {}
  LazySegmentTree(const vector<T>& a): n((int)a.size()) {
    while(size < (int)a.size()) {
      size <<= 1;
      log++;
    }
    tree = vector<T>(size << 1, one);
    lazy = vector<F>(size, identity);
    for(int i = size + a.size() - 1; i >= 1; i--)
      if(i >= size) tree[i] = a[i - size];
      else _consume(i);
  }
  void set(int i, T x) {
    i += size;
    _flush_to_leaf(i);
    tree[i] = x;
    _consume_to_root(i);
  }
  void update(int i, T x) {
    i += size;
    _flush_to_leaf(i);
    tree[i] = op(tree[i], x);
    _consume_to_root(i);
  }
  T get(int i) {
    i += size;
    _flush_to_leaf(i);
    return tree[i];
  }
  T prod(int l, int r) {
    if(l == r + 1) return T();
    l += size; 
    r += size + 1;
    for(int i = log; i >= 1; i--) {
      if(((l >> i) << i) != l) _flush(l >> i); 
      if(((r >> i) << i) != r) _flush((r - 1) >> i);
    }
    T pl = one, pr = one;
    for(; l < r; l >>= 1, r >>= 1) {
      if(l & 1) pl = op(pl, tree[l++]);
      if(r & 1) pr = op(tree[--r], pr);
    }
    return op(pl, pr);
  }
  T total_prod() { return tree[1]; }
  void apply(int i, F f) {
    i += size;
    _flush_to_leaf(i);
    tree[i] = apply_(f, tree[i]);
    _consume_to_root(i);
  }
  void apply(int l, int r, F f) {
    if(l == r + 1) return;
    l += size;
    r += size + 1;
    for(int i = log; i >= 1; i--) {
      if(((l >> i) << i) != l) _flush(l >> i); 
      if(((r >> i) << i) != r) _flush((r - 1) >> i);
    }
    for(int l2 = l, r2 = r; l2 < r2; l2 >>= 1, r2 >>= 1) {
      if(l2 & 1) _apply_to_node(l2++, f);
      if(r2 & 1) _apply_to_node(--r2, f);
    }
    for(int i = 1; i <= log; i++) {
      if(((l >> i) << i) != l) _consume(l >> i); 
      if(((r >> i) << i) != r) _consume((r - 1) >> i);
    }
  }
  int first_true_from_left(function<bool(T)> f, int l = 0) {
    assert(!f(one));
    assert(0 <= l && l <= n);
    if(l == n) return n;
    l += size;
    _flush_to_leaf(l);
    T p = one;
    do {
      while(!(l & 1)) l >>= 1;
      if(f(op(p, tree[l]))) {
        while(l < size) {
          _flush(l);
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
    _flush_to_leaf(_r);
    T p = one;
    do {
      while(_r > 1 && _r & 1) _r >>= 1;
      if(f(op(tree[_r], p))) {
        while(_r < size) {
          _flush(_r);
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
  void _apply_to_node(int i, F f) {
    tree[i] = apply_(f, tree[i]);
    if(i < size) lazy[i] = compose(f, lazy[i]);
  }
  void _consume(int i) { tree[i] = op(tree[i << 1], tree[i << 1 | 1]); }
  void _consume_to_root(int i) { for(i >>= 1; i >= 1; i >>= 1) _consume(i); }
  void _flush(int i) {
    _apply_to_node(i << 1, lazy[i]);
    _apply_to_node(i << 1 | 1, lazy[i]);
    lazy[i] = identity;
  }
  void _flush_to_leaf(int i) { for(int j = log; j >= 1; j--) _flush(i >> j); }
};

#endif
