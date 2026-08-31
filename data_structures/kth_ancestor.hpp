#ifndef KTH_ANCESTOR_HPP
#define KTH_ANCESTOR_HPP

#include "starter.hpp"

struct KthAncestor {
  int n, log = 1;
  vector<vector<int>> par;
  KthAncestor() = default;
  KthAncestor(const vector<int>& p) : n((int)p.size()) {
    while((1 << log) <= n) log++;
    par.resize(log);
    FOR(i,log) par[i].resize(n);
    par[0] = p;
    FORR(i,1,log-1) FOR(j,n)
      par[i][j] = par[i - 1][j] == -1 ? -1 : par[i - 1][par[i - 1][j]];
  }
  int query(int u, int k) {
    int ret = u;
    while(k && ret != -1) {
      int lo = (k & -k);
      ret = par[31 - __builtin_clz(lo)][ret];
      k -= lo;
    } 
    return ret;
  }
};

#endif
