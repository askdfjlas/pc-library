#include "data_structures/li_chao_tree.hpp"
#include "starter.hpp"

const int INF = 1e9;

// https://judge.yosupo.jp/problem/line_add_get_min
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_sinces_epoch().count());

  LiChaoTree<ll,-INF,INF> tree;
  int n, q;
  cin >> n >> q;
  FOR(i,n) {
    ll a, b;
    cin >> a >> b;
    tree.add(a, b);
  }
  while(q--) {
    ll t, a, b;
    cin >> t;
    if(t == 0) {
      cin >> a >> b;
      tree.add(a, b);
    }
    else {
      cin >> a;
      cout << tree.query(a) << '\n';
    }
  }
}

