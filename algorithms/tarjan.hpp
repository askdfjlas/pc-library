#ifndef TARJAN_HPP
#define TARJAN_HPP

#include "starter.hpp"

/*
 * 0 <= res[i] < adj.size()
 * res[i] == res[j] <=> i and j in same SCC
 * 
 * There exists some topological ordering such that for all i, j,
 * res[i] < res[j] <=> i occurs before j in the ordering
 */
vector<int> tarjan(vector<vector<int>>& g) {
  int n = (int)g.size(), t = 0, cnt = n - 1;
  vector<char> vis(n);
  vector<int> in(n), res(n), stk;
  function<void(int)> dfs = [&](int cur) {
    in[cur] = res[cur] = t++;
    vis[cur]++;
    stk.push_back(cur);
    for(int v : g[cur]) {
      if(!vis[v]) dfs(v);
      if(vis[v] == 1) res[cur] = min(res[cur], res[v]);
    }
    if(in[cur] == res[cur]) {
      while(1) {
        int v = stk.back();
        stk.pop_back(); 
        res[v] = cnt; 
        vis[v]++;
        if(v == cur) break;
      }
      cnt--;
    }
  };
  FOR(i,n) if(!vis[i]) dfs(i); 
  int m = *min_element(res.begin(), res.end());
  for(int& v : res) v -= m;
  return res;
}

#endif