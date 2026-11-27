#ifndef MISC_HPP
#define MISC_HPP

#include "starter.hpp"

namespace misc {
  template<ranges::input_range R>
  vector<vector<ranges::range_value_t<R>>> compute_runs(
    R&& range,
    function<bool(ranges::range_value_t<R>, ranges::range_value_t<R>)> is_same_run
   ) {
    using T = ranges::range_value_t<R>;
    auto begin = ranges::begin(range);
    auto end = ranges::end(range);
    vector<vector<T>> res;
    while(begin != end) {
      vector<T> cur = {*begin};
      begin++;
      while(begin != end && is_same_run(cur.back(), *begin)) {
        cur.push_back(*begin);
        begin++;
      }
      res.push_back(cur);
    }
    return res;
  }
  
  template<ranges::input_range R>
  vector<pair<ranges::range_value_t<R>, int>> compute_run_lengths(R&& range) {
    using T = ranges::range_value_t<R>;
    auto begin = ranges::begin(range);
    auto end = ranges::end(range);
    vector<pair<T, int>> res;
    while(begin != end) {
      auto cur = *begin;
      int cnt = 0;
      while(begin != end && *begin == cur) {
        begin++;
        cnt++;
      }
      res.push_back({cur, cnt});
    }
    return res;
  }
}

#endif