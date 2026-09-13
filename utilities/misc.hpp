#ifndef MISC_HPP
#define MISC_HPP

#include "starter.hpp"

namespace misc {
  template<ranges::input_range R>
  vector<pair<ranges::range_value_t<R>, int>> compute_runs(R&& range) {
    auto begin = ranges::begin(range);
    auto end = ranges::end(range);
    vector<pair<ranges::range_value_t<R>, int>> res;
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