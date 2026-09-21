#ifndef FREQUENT_LAZY_SEGMENT_TREES_HPP
#define FREQUENT_LAZY_SEGMENT_TREES_HPP

#include "data_structures/segment_tree/lazy_segment_tree.hpp"
#include "starter.hpp"

namespace frequent_lazy_segment_trees {
  struct SMM {
    ll sum;
    int min_, max_, len;
    constexpr SMM() : SMM(0) {}
    constexpr SMM(int x) : sum(x), min_(x), max_(x), len(1) {}
    constexpr SMM(ll sum_, int min__, int max__, int len_) :
      sum(sum_), min_(min__), max_(max__), len(len_) {}
  };
  
  SMM smm_op(SMM a, SMM b) {
    return SMM(
      a.sum + b.sum,
      min(a.min_, b.min_),
      max(a.max_, b.max_),
      a.len + b.len
    );
  }
  
  constexpr SMM smm_one = SMM(0, INT_MAX, INT_MIN, 0);
  
  namespace add {
    SMM apply(int f, SMM x) { return SMM(x.sum + (ll)f * x.len, x.min_ + f, x.max_ + f, x.len); }
    int compose(int f1, int f2) { return f1 + f2; }
    const int identity = 0;
  }
  
  // Remember that [INT_MIN] is the identity
  namespace set_ {
    SMM apply(int f, SMM x) { return f != INT_MIN ? SMM((ll)f * x.len, f, f, x.len) : x; }
    int compose(int f1, int f2) { return f1 != INT_MIN ? f1 : f2; }
    const int identity = INT_MIN;
  }
  
  using SMMAddInt = LazySegmentTree<SMM, smm_op, smm_one, int, add::apply, add::compose, add::identity>;
  using SMMSetInt = LazySegmentTree<SMM, smm_op, smm_one, int, set_::apply, set_::compose, set_::identity>;
}

#endif