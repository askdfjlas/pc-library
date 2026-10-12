#ifndef OFFLINE_SEQUENCE_HPP
#define OFFLINE_SEQUENCE_HPP

#include "data_structures/fenwick_tree.hpp"
#include "starter.hpp"

template <class T> struct OfflineSequence {
  vector<pair<int, T>> insertions;
  vector<T> get() {
    int n = (int)insertions.size();
    vector<T> res(n);
    FenwickTree<int> tree(vector<int>(n, 1));
    for(int j = n - 1; j >= 0; j--) {
      auto [i, x] = insertions[j];
      int real_i = tree.lower_bound(i + 1);
      tree.update(real_i, -1);
      res[real_i] = x;
    }
    return res;
  }
  void insert(int i, T x) {
    assert(0 <= i && i <= (int)insertions.size());
    insertions.push_back({i, x});
  }
};

#endif