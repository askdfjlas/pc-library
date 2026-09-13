#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include "starter.hpp"

template <class T> struct SquareMatrix {
  int n;
  vector<T> mat;
  static SquareMatrix one(int n_) {
    SquareMatrix res(n_);
    FOR(i,n_) res[i][i] = T{1};
    return res;
  }
  SquareMatrix(int n_) : n(n_), mat(n_ * n_) {}
  T* operator[](int i) { return &mat[i * n]; }
  const T* operator[](int i) const { return &mat[i * n]; }
  SquareMatrix operator*(SquareMatrix& rhs) {
    SquareMatrix res(n);
    FOR(i,n) FOR(j,n) FOR(k,n)
      res[i][j] += (*this)[i][k] * rhs[k][j];
    return res;
  }
  vector<T> operator*(vector<T>& rhs) {
    vector<T> res(n);
    FOR(i,n) FOR(j,n)
      res[i] += (*this)[i][j] * rhs[j];
    return res;
  }
  SquareMatrix pow(ll p) {
    SquareMatrix res = one(n), x = *this;
    while(p > 0) {
      if(p & 1) res = res * x;
      p >>= 1;
      x = x * x;
    }
    return res;
  }
};

#endif