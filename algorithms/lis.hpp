#ifndef LIS_HPP
#define LIS_HPP

#include "starter.hpp"

namespace lis {
  template <typename T> vector<int> strictly_increasing(vector<T>& a) {
    int n = (int)a.size(), len = 0;
    T l = numeric_limits<T>::min(), h = numeric_limits<T>::max();
    vector<pair<T,int>> dp(n + 1, {h, INT_MAX});
    dp[0] = {l, -1};
    vector<int> p(n);
    FOR(i,n) {
      int j = lower_bound(dp.begin(), dp.end(), {a[i], 0}) - dp.begin();
      dp[j] = {a[i], i};
      p[i] = dp[j - 1].second;
      len = max(len, j);
    }
    auto [_, i] = dp[len];
    vector<int> res;
    while(i != -1) {
      res.push_back(i);
      i = p[i];
    }
    reverse(res.begin(), res.end());
    return res;
  }
  
  template <typename T> vector<int> nondecreasing(vector<T>& a) {
    int n = (int)a.size(), len = 0;
    T l = numeric_limits<T>::min(), h = numeric_limits<T>::max();
    vector<pair<T,int>> dp(n + 1, {h, INT_MAX});
    dp[0] = {l, -1};
    vector<int> p(n);
    FOR(i,n) {
      int j = upper_bound(dp.begin(), dp.end(), {a[i], INT_MAX - 1}) - dp.begin();
      dp[j] = {a[i], i};
      p[i] = dp[j - 1].second;
      len = max(len, j);
    }
    auto [_, i] = dp[len];
    vector<int> res;
    while(i != -1) {
      res.push_back(i);
      i = p[i];
    }
    reverse(res.begin(), res.end());
    return res;
  }
}

#endif