#ifndef LICHAOTREE_HPP
#define LICHAOTREE_HPP

#include "starter.hpp"

template <typename T, T LO, T HI, class C = less<T>> struct LiChaoTree {
  struct Line {
    T m, b;
    int l = -1, r = -1;
    Line(T m_, T b_) : m(m_), b(b_) {}
    T operator()(T x) { return m*x + b; }
  };
  vector<Line> tree;
  T query(int id, T l, T r, T x) {
    auto& line = tree[id];
    T mid = (l + r)/2, ans = line(x);
    if(line.l != -1 && x <= mid)
      ans = _choose(ans, query(line.l, l, mid, x));
    else if(line.r != -1 && x > mid)
      ans = _choose(ans, query(line.r, mid + 1, r, x));
    return ans;
  }
  T query(T x) { return query(0, LO, HI, x); }
  int add(int id, T l, T r, T m, T b) {
    if(tree.empty() || id == -1) {
      tree.push_back(Line(m, b));
      return (int)tree.size() - 1; 
    }
    auto& line = tree[id];
    T mid = (l + r)/2;
    if(C()(m*mid + b, line(mid))) {
      swap(m, line.m);
      swap(b, line.b);
    }
    if(C()(m, line.m) && l != r) tree[id].r = add(line.r, mid + 1, r, m, b);
    else if(l != r) tree[id].l = add(line.l, l, mid, m, b);
    return id;
  }
  void add(T m, T b) { add(0, LO, HI, m, b); }
  T _choose(T x, T y) { return C()(x, y) ? x : y; }
};

#endif