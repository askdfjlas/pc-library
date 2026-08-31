#include "algorithms/enumerate_triangles.hpp"
#include "starter.hpp"

const ll MOD = 998244353;

// https://judge.yosupo.jp/problem/enumerate_triangles
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  int n, m;
  cin >> n >> m;
  
  ll x[n];
  vector<pair<int,int>> edges(m);
  FOR(i,n) cin >> x[i];
  FOR(i,m) cin >> edges[i].first >> edges[i].second;
  
  ll ans = 0;
  enumerate_triangles(edges, [&](int i, int j, int k) {
    ll contr = (x[i] * x[j]) % MOD;
    ans = (ans + contr * x[k]) % MOD;
  });
  cout << ans << '\n';
}
