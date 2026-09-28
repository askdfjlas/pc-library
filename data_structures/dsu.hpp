#ifndef DSU_HPP
#define DSU_HPP

#include "starter.hpp"

struct Dsu {
  vector<int> p, s;
  Dsu(int n) {
    p.resize(n);
    s.resize(n);
    FOR(i,n) {
      p[i] = i;
      s[i] = 1;
    }
  }
  int get(int u) {
    int t = u;
    while(p[t] != t) t = p[t];
    while(p[u] != u) {
      int n = p[u];
      p[u] = t;
      u = n;
    }
    return t;
  }
  int join(int u, int v) {
    int a = get(u), b = get(v);
    if(a == b) return -1;
    if(s[a] < s[b]) swap(a, b);
    s[a] += s[b];
    p[b] = a;
    return a;
  }
};

#endif