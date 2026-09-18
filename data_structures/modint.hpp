#ifndef MODINT_HPP
#define MODINT_HPP

#include "starter.hpp"
#include "utilities/math.hpp"

template <unsigned int MOD> struct Mint {
  unsigned int v;
  Mint() : v(0) {}
  Mint(ll v_) {
    if(v_ < 0) [[unlikely]] v = (v_ % MOD) + MOD;
    else if(v_ >= MOD) [[unlikely]] v = v_ % MOD;
    else v = v_;
  }
  Mint& operator+=(const Mint& rhs) {
    v += rhs.v;
    if(v >= MOD) v -= MOD;
    return *this;
  }
  Mint& operator-=(const Mint& rhs) {
    if(*this < rhs) v += MOD;
    v -= rhs.v;
    return *this;
  }
  Mint& operator*=(const Mint& rhs) {
    unsigned long long v_ = v;
    v = (v_ * rhs.v) % MOD;
    return *this;
  }
  Mint& operator/=(const Mint& rhs) { return operator*=(rhs.inv()); }
  friend Mint operator+(const Mint& lhs, const Mint& rhs) { return Mint(lhs) += rhs; }
  friend Mint operator-(const Mint& lhs, const Mint& rhs) { return Mint(lhs) -= rhs; }
  friend Mint operator*(const Mint& lhs, const Mint& rhs) { return Mint(lhs) *= rhs; }
  friend Mint operator/(const Mint& lhs, const Mint& rhs) { return Mint(lhs) /= rhs; }
  Mint& operator++() {
    v++;
    if(v == MOD) v = 0;
    return *this;
  }
  Mint operator++(int) {
    Mint r = *this;
    ++*this;
    return r;
  }
  Mint& operator--() {
    if(v == 0) v = MOD;
    v--;
    return *this;
  }
  Mint operator--(int) {
    Mint r = *this;
    --*this;
    return r;
  }
  bool operator==(const Mint& rhs) { return v == rhs.v; }
  bool operator!=(const Mint& rhs) { return v != rhs.v; }
  bool operator<(const Mint& rhs) { return v < rhs.v; }
  bool operator<=(const Mint& rhs) { return v <= rhs.v; }
  bool operator>(const Mint& rhs) { return v > rhs.v; }
  bool operator>=(const Mint& rhs) { return v >= rhs.v; }
  Mint pow(ll p) const { return math::pow_mod(v, p, MOD); }
  Mint inv() const { return pow(MOD - 2); }
  friend ostream& operator<<(ostream& os, const Mint rhs) { return os << rhs.v; }
  friend istream& operator>>(istream& is, Mint& rhs) { return is >> rhs.v; }
};

#endif
