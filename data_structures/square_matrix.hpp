#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include "starter.hpp"

template <ll MOD = 1e9 + 7> struct SquareMatrix {
  vector<vector<ll>> mat;
  SquareMatrix(int n) {
    mat.resize(n);
    FOR(i,n) {
      mat[i].resize(n);
      mat[i][i] = 1;
    }
  }
  static SquareMatrix zero(int n) {
    SquareMatrix ret(n);
    FOR(i,n) ret.mat[i][i] = 0;
    return ret;
  }
  SquareMatrix operator*(SquareMatrix& other) {
    int n = (int)mat.size();
    SquareMatrix ret = zero(n);
    FOR(i,n) FOR(j,n) FOR(k,n) {
      ll inc = (mat[i][k] * other.mat[k][j]) % MOD;
      ret.mat[i][j] = (ret.mat[i][j] + inc) % MOD;
    }
    return ret;
  }
  SquareMatrix exp(ll p) {
    SquareMatrix ret((int)mat.size()), x = *this;
    while(p > 0) {
      if(p & 1) ret = ret * x;
      p >>= 1;
      x = x * x;
    }
    return ret;
  }
};

#endif