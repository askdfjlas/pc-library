#ifndef FREQUENT_SEGMENT_TREES_HPP
#define FREQUENT_SEGMENT_TREES_HPP

#include "data_structures/segment_tree/segment_tree.hpp"
#include "starter.hpp"

namespace frequent_segment_trees {
  int max_op(int a, int b) { return max(a, b); }
  int min_op(int a, int b) { return min(a, b); }
  
  ll max_op(ll a, ll b) { return max(a, b); }
  ll min_op(ll a, ll b) { return min(a, b); }
  
  using MaxInt = SegmentTree<int, max_op, INT_MIN>;
  using MinInt = SegmentTree<int, min_op, INT_MAX>;
  
  using MaxLL = SegmentTree<ll, max_op, LLONG_MIN>;
  using MinLL = SegmentTree<ll, min_op, LLONG_MAX>;
}

#endif