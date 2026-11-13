#ifndef DYNAMIC_SEGMENT_TREE_HPP
#define DYNAMIC_SEGMENT_TREE_HPP

#include "starter.hpp"

template <
  class T,
  T (*op)(T, T),
  T one,
  typename Index = int,
  auto compute_node = [](Index l [[maybe_unused]], Index r [[maybe_unused]]) { return one; }
>
 struct DynamicSegmentTree {
  struct Node {
    T x;
    int l, r;
  };
  Index n;
  vector<Node> tree;
  vector<int> roots;
  DynamicSegmentTree(Index n_) : n(n_) {
    tree.push_back(Node(compute_node(0, n - 1), -1, -1));
    roots.push_back(0);
  }
  DynamicSegmentTree(const vector<T>& a) : DynamicSegmentTree((int)a.size()) { FOR(i,n) set(i, a[i]); }
  T get(Index i, optional<int> version = nullopt) { return prod(i, i, version); }
  void set(Index i, T x) {
    assert((int)roots.size() == 1);
    _set(0, 0, n - 1, i, x);
  }
  void set_persistent(Index i, T x, optional<int> old_version = nullopt) {
    int _old_version = old_version.value_or(version_count() - 1);
    assert(0 <= _old_version && _old_version < version_count());
    _set_persistent(roots[_old_version], 0, n - 1, i, x);
    roots.push_back((int)tree.size() - 1);
  }
  void update(Index i, T x) { set(i, op(get(i), x)); }
  void update_persistent(Index i, T x, optional<int> old_version = nullopt) {
    set_persistent(i, op(get(i, old_version), x), old_version);
  }
  T prod(Index l, Index r, optional<int> version = nullopt) {
    assert(0 <= l && l <= r + 1 && r < n);
    int _version = version.value_or(version_count() - 1);
    assert(0 <= _version && _version < version_count());
    if(l == r + 1) return one;
    return _prod(roots[_version], 0, n - 1, l, r);
  }
  T total_prod(optional<int> version = nullopt) {
    int _version = version.value_or(version_count() - 1);
    assert(0 <= _version && _version < version_count());
    return tree[roots[_version]].x;
  }
  int version_count() { return (int)roots.size(); }
  T _prod(int i, Index l, Index r, Index ql, Index qr) {
    if(ql <= l && qr >= r) return tree[i].x;
    T p = one;
    Index m = l + (r - l)/2;
    if(ql <= m) {
      T pl = tree[i].l != -1 ? _prod(tree[i].l, l, m, ql, qr) : compute_node(l, m);
      p = op(p, pl);
    }
    if(qr > m && tree[i].r != -1) {
      T pr = tree[i].r != -1 ? _prod(tree[i].r, m + 1, r, ql, qr) : compute_node(m + 1, r);
      p = op(p, pr);
    }
    return p;
  }
  void _set(int i, Index l, Index r, Index si, T x) {
    if(l == r) {
      tree[i].x = x;
      return;
    }
    Index m = l + (r - l)/2;
    if(si <= m) {
      if(tree[i].l == -1) _create_left_child(i, l, m);
      _set(tree[i].l, l, m, si, x);
    }
    else {
      if(tree[i].r == -1) _create_right_child(i, m + 1, r);
      _set(tree[i].r, m + 1, r, si, x);
    }
    T pl = tree[i].l == -1 ? compute_node(l, m) : tree[tree[i].l].x;
    T pr = tree[i].r == -1 ? compute_node(m + 1, r) : tree[tree[i].r].x;
    tree[i].x = op(pl, pr);
  }
  void _set_persistent(int i, Index l, Index r, Index si, T x) {
    if(l == r) {
      tree.push_back(Node(x, -1, -1));
      return;
    }
    Index m = l + (r - l)/2;
    Node cpy = tree[i];
    if(si <= m) {
      if(tree[i].l == -1) _create_left_child(i, l, m);
      _set_persistent(tree[i].l, l, m, si, x);
      cpy.l = (int)tree.size() - 1;
    }
    else {
      if(tree[i].r == -1) _create_right_child(i, m + 1, r);
      _set_persistent(tree[i].r, m + 1, r, si, x);
      cpy.r = (int)tree.size() - 1;
    }
    T pl = cpy.l == -1 ? compute_node(l, m) : tree[cpy.l].x;
    T pr = cpy.r == -1 ? compute_node(m + 1, r) : tree[cpy.r].x;
    cpy.x = op(pl, pr);
    tree.push_back(cpy);
  }
  void _create_left_child(int i, Index l, Index r) {
    tree[i].l = (int)tree.size();
    tree.push_back(Node(compute_node(l, r), -1, -1));
  }
  void _create_right_child(int i, Index l, Index r) {
    tree[i].r = (int)tree.size();
    tree.push_back(Node(compute_node(l, r), -1, -1));
  }
};

#endif
