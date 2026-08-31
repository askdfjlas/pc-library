#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <ext/pb_ds/assoc_container.hpp>
#include "starter.hpp"
 
struct splitmix64 {
  size_t operator()(size_t x) const {
    static const size_t fixed = chrono::steady_clock::now().time_since_epoch().count();
    x += 0x9e3779b97f4a7c15 + fixed;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};
 
template<typename K, typename V>
using hash_table = __gnu_pbds::gp_hash_table<K, V, splitmix64>;

#endif