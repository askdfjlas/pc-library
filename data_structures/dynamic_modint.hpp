#ifndef DYNAMIC_modINT_HPP
#define DYNAMIC_modINT_HPP

#include "starter.hpp"
#include "utilities/math.hpp"

struct DynamicMint {
  unsigned int v;
  inline static unsigned int mod;
  static void set_mod(int mod_) { mod = mod_; }
  DynamicMint() : v(0) {}
  DynamicMint(ll v_) {
    if(v_ < 0) [[unlikely]] v = (v_ % mod) + mod;
    else if(v_ >= mod) [[unlikely]] v = v_ % mod;
    else v = v_;
  }
  DynamicMint& operator+=(const DynamicMint& rhs) {
    v += rhs.v;
    if(v >= mod) v -= mod;
    return *this;
  }
  DynamicMint& operator-=(const DynamicMint& rhs) {
    if(*this < rhs) v += mod;
    v -= rhs.v;
    return *this;
  }
  DynamicMint& operator*=(const DynamicMint& rhs) {
    unsigned long long v_ = v;
    v = (v_ * rhs.v) % mod;
    return *this;
  }
  friend DynamicMint operator+(const DynamicMint& lhs, const DynamicMint& rhs) { return DynamicMint(lhs) += rhs; }
  friend DynamicMint operator-(const DynamicMint& lhs, const DynamicMint& rhs) { return DynamicMint(lhs) -= rhs; }
  friend DynamicMint operator*(const DynamicMint& lhs, const DynamicMint& rhs) { return DynamicMint(lhs) *= rhs; }
  friend DynamicMint operator/(const DynamicMint& lhs, const DynamicMint& rhs) { return DynamicMint(lhs) /= rhs; }
  DynamicMint& operator++() {
    v++;
    if(v == mod) v = 0;
    return *this;
  }
  DynamicMint operator++(int) {
    DynamicMint r = *this;
    ++*this;
    return r;
  }
  DynamicMint& operator--() {
    if(v == 0) v = mod;
    v--;
    return *this;
  }
  DynamicMint operator--(int) {
    DynamicMint r = *this;
    --*this;
    return r;
  }
  bool operator==(const DynamicMint& rhs) { return v == rhs.v; }
  bool operator!=(const DynamicMint& rhs) { return v != rhs.v; }
  bool operator<(const DynamicMint& rhs) { return v < rhs.v; }
  bool operator<=(const DynamicMint& rhs) { return v <= rhs.v; }
  bool operator>(const DynamicMint& rhs) { return v > rhs.v; }
  bool operator>=(const DynamicMint& rhs) { return v >= rhs.v; }
  DynamicMint pow(ll p) const { return math::pow_mod(v, p, mod); }
  DynamicMint inv() const { return pow(mod - 2); }
  friend ostream& operator<<(ostream& os, const DynamicMint rhs) { return os << rhs.v; }
  friend istream& operator>>(istream& is, DynamicMint& rhs) { return is >> rhs.v; }
};

#endif
