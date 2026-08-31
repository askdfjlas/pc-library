#include "data_structures/lca.hpp"
#include "starter.hpp"

// https://judge.yosupo.jp/problem/lca
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  int n, q;
  cin >> n >> q;
  vector<int> p(n);
  FOR(i,n-1) cin >> p[i + 1];
  LCA o(p);
  FOR(i,q) {
    int u, v;
    cin >> u >> v;
    cout << o.lca(u, v) << '\n';
  }
}
