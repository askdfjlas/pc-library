#ifndef SIMPLE_WAVELET_MATRIX_HPP
#define SIMPLE_WAVELET_MATRIX_HPP

#include "data_structures/wavelet_matrix.hpp"
#include "starter.hpp"

namespace simple_wavelet_matrix {
  monostate nothing_op(monostate, monostate) { return {}; }
  
  struct NothingSummer {
    NothingSummer(vector<monostate>) {}
    monostate range_sum(int, int) { return {}; }
    void update(int, monostate) {}
    void set(int, monostate) {}
  }; 
}

template <typename Key = int>
struct SimpleWaveletMatrix {
  using Wavelet = 
    WaveletMatrix<
      monostate,
      simple_wavelet_matrix::nothing_op,
      {},
      simple_wavelet_matrix::NothingSummer,
      Key
    >;
  Wavelet wavelet;
  SimpleWaveletMatrix(vector<Key>& a): wavelet(
    [&]() {
      vector<pair<Key, monostate>> b((int)a.size());
      FOR(i,(int)a.size()) b[i] = {a[i], {}};
      return b;
    }()
  ) {}
  Key kth_smallest(int l, int r, int k) { return wavelet.kth_smallest(l, r, k).first; }
};

#endif