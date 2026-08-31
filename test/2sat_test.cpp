#include "algorithms/2sat.hpp"
#include "starter.hpp"

// https://judge.yosupo.jp/problem/two_sat
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  string s;
  int n, m, ig;
  cin >> s >> s >> n >> m;
  vector<pair<int,int>> clauses(m);
  FOR(i,m) cin >> clauses[i].first >> clauses[i].second >> ig;
  auto [sol, x] = sat2(n, clauses);
  if(!sol) {
    cout << "s UNSATISFIABLE\n";
    exit(0);
  }
  cout << "s SATISFIABLE\nv ";
  for(int i = 1; i <= n; i++) {
    if(x[i - 1]) cout << i << ' ';
    else cout << -i << ' ';
  }
  cout << "0\n";
}
