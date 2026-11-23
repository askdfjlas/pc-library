#ifndef WAVELET_MATRIX
#define WAVELET_MATRIX

#include "starter.hpp"
#include "utilities/bits.hpp"

/*
[RangeSummer] gets constructed with some [vector<T> a] and should support the following operations:

- [range_sum(int l, int r)] should return [a[l] + a[l + 1] + ... + a[r]]
- [update(int i, T delta)] should set [a[i]] to [a[i] + delta]
- [set(int i, T x)] should set [a[i]] to [x]

In particular, [FenwickTree<T>] satisfies this interface
*/
template <class T, T (*op)(T, T), T one, class RangeSummer, typename Key = int>
struct WaveletMatrix {
  int layers;
  vector<Key> keys;
  vector<vector<int>> prefs;
  vector<RangeSummer> range_summers;
  WaveletMatrix(const vector<pair<Key, T>>& a) {
    int n = (int)a.size();
    layers = bits::high_bit_index(n);
    layers += (n & (n - 1)) > 0;
    keys.resize(n);
    FOR(i,n) keys[i] = a[i].first;
    sort(keys.begin(), keys.end());
    vector<tuple<Key, T, int, int>> order, l, r;
    order.resize(n); 
    FOR(i,n) order[i] = {a[i].first, a[i].second, 0, n - 1};
    vector<int> pref;
    pref.reserve(n + 1);
    l.reserve(n); r.reserve(n);
    FOR(_,layers) {
      pref = {0};
      for(auto [k, w, kl, kr]: order) {
        int km = (kl + kr)/2;
        if(k > keys[km]) {
          r.emplace_back(k, w, km + 1, kr);
          pref.push_back(pref.back());
        }
        else {
          l.emplace_back(k, w, kl, km);
          pref.push_back(pref.back() + 1);
        }
      }
      swap(order, l);
      order.insert(order.end(), r.begin(), r.end());
      prefs.push_back(pref);
      vector<T> ts(n);
      FOR(i,n) ts[i] = get<1>(order[i]);
      range_summers.emplace_back(ts);
      l.clear(); r.clear();
    }
  }
  // "smallest" and "largest" correspond to the strict ordering created from (key, original index)
  pair<Key, T> kth_smallest(int l, int r, int k) {
    assert(0 <= l && l <= r && r < (int)keys.size());
    int kl = 0, kr = (int)keys.size() - 1;
    FOR(i,layers) {
      auto& pref = prefs[i];
      int cnt_l = pref[r + 1] - pref[l];
      int km = (kl + kr)/2;
      if(k <= cnt_l) {
        l = pref[l], r = pref[r + 1] - 1;
        kr = km;
      }
      else {
        l = pref.back() + l - pref[l], r = pref.back() + r - pref[r + 1];
        k -= cnt_l;
        kl = km + 1;
      }
    }
    return {keys[kl], range_summers.back().range_sum(l + k - 1, l + k - 1)};
  }
  pair<Key, T> kth_largest([[maybe_unused]] int l, [[maybe_unused]] int r, [[maybe_unused]] int k) {
    // Will implement someday...
    assert(false);
    return {Key(0), T(0)};
  }
  /*
  Let [b[l], b[l + 1], ..., b[r]] be [a[l], a[l + 1], ..., a[r]] stable-sorted by key. Let t(i), where l <= i <= r, be 
  the tuple (number of elements, sum of Ts) that corresponds to b[l...i]. Assuming that [f] is monotonic on 
  [t(l), t(l + 1), ..., t(r)], returns the first t(i) such that f(t(i)) returns true, along with the highest key. If it
  never returns true, returns {...t(r), b[r]'s key}
  */
  tuple<int, T, Key> first_true_from_lowest_keys(
    [[maybe_unused]] int l,
    [[maybe_unused]] int r,
    [[maybe_unused]] function<bool(int, T)> f
  ) {
    // Will implement someday...
    assert(false);
    return {0, T(0), Key(0)};
  }
  // 
  // Same as [first_true_from_lowest_keys] but deals with suffixes of [b]
  tuple<int, T, Key> first_true_from_highest_keys(int l, int r, function<bool(int, T)> f) {
    assert(0 <= l && l <= r && r < (int)keys.size());
    int cnt = 0, kl = 0, kr = (int)keys.size() - 1;
    T acc = one;
    FOR(i,layers) {
      auto& pref = prefs[i];
      int cnt_l = pref[r + 1] - pref[l];
      int cnt_r = (r - l + 1) - cnt_l;
      int l_r = pref.back() + l - pref[l], r_r = pref.back() + r - pref[r + 1];
      int km = (kl + kr)/2;
      T sum_r = range_summers[i].range_sum(l_r, r_r);
      T acc_r = op(acc, sum_r);
      if(f(cnt + cnt_r, acc_r) && kl < kr) {
        l = l_r, r = r_r;
        kl = km + 1;
      }
      else {
        l = pref[l], r = pref[r + 1] - 1;
        kr = km;
        acc = acc_r;
        cnt += cnt_r;
      }
    }
    int bl = l, br = r;
    while(bl <= br) {
      int m = (bl + br)/2;
      T acc_m = op(acc, range_summers.back().range_sum(m, r));
      if(f(cnt + r - m + 1, acc_m)) bl = m + 1;
      else br = m - 1;
    }
    br = max(br, l);
    cnt += r - br + 1;
    acc = op(acc, range_summers.back().range_sum(br, r));
    return {cnt, acc, keys[kl]};
  }
  void set(int i, T x) {
    FOR(_i,layers) {
      auto& pref = prefs[_i];
      if(pref[i + 1] - pref[i]) i = pref[i];
      else i = pref.back() + i - pref[i];
      range_summers[_i].set(i, x);
    }
  }
  void update(int i, T delta) {
    FOR(_i,layers) {
      auto& pref = prefs[_i];
      if(pref[i + 1] - pref[i]) i = pref[i];
      else i = pref.back() + i - pref[i];
      range_summers[_i].update(i, delta);
    }
  }
};

#endif