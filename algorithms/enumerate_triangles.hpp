#ifndef ENUMERATE_TRIANGLES_HPP
#define ENUMERATE_TRIANGLES_HPP

#include "starter.hpp"

void enumerate_triangles(vector<pair<int,int>>& edges, function<void(int,int,int)> f) {
  int n = 0;
  for(auto [u, v] : edges) n = max({n, u + 1, v + 1});
  vector<int> deg(n);
  vector<int> g[n];
  for(auto [u, v] : edges) {
    deg[u]++;
    deg[v]++;
  }
  for(auto [u, v] : edges) {
    if(u == v) continue;
    if(deg[u] > deg[v] || (deg[u] == deg[v] && u > v))
      swap(u, v);
    g[u].push_back(v);
  }
  vector<int> flag(n);
  for(int i = 0; i < n; i++) {
    for(int v : g[i]) flag[v] = 1;
    for(int v : g[i]) for(int u : g[v]) {
      if(flag[u]) f(i, v, u);
    }
    for(int v : g[i]) flag[v] = 0;
  }
}

#endif