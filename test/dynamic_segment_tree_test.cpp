#include "data_structures/segment_tree/dynamic_segment_tree.hpp"
#include "starter.hpp"

ll sum_op(ll a, ll b) { return a + b; }

using segtree = DynamicSegmentTree<ll,sum_op,0>;

// https://judge.yosupo.jp/problem/point_add_range_sum
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  FOR(i,n) cin >> a[i];
  segtree tree(a);
  FOR(_,q) {
    int t;
    cin >> t;
    if(t == 0) {
      int i, x;
      cin >> i >> x;
      tree.update(i, x);
    }
    else {
      int l, r;
      cin >> l >> r;
      r--;
      cout << tree.prod(l, r) << '\n';
    }
  }
}
