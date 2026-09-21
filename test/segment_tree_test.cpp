#include "data_structures/segment_tree/frequent_segment_trees.hpp"
#include "starter.hpp"

// https://atcoder.jp/contests/practice2/tasks/practice2_j
// 44ms (without the redundant segtree) for n, q <= 2e5
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n, q;
  cin >> n >> q;
  vector<int> a(n + 1);
  FORR(i,1,n) cin >> a[i];
  frequent_segment_trees::MaxInt tree(a);
  reverse(a.begin(), a.end());
  frequent_segment_trees::MaxInt tree_rev(a);  // redundant but used to test [first_true_from_right]
  FOR(_,q) {
    int t;
    cin >> t;
    if(t == 1) {
      int x, v;
      cin >> x >> v;
      tree.set(x, v);
      int x_rev = n - x;
      tree_rev.set(x_rev, v);
    }
    else if(t == 2) {
      int l, r;
      cin >> l >> r;
      int r1 = tree.prod(l, r);
      int l_rev = n - l, r_rev = n - r;
      int r2 = tree_rev.prod(r_rev, l_rev);
      assert(r1 == r2);
      cout << r1 << '\n';
    }
    else {
      int l, v;
      cin >> l >> v;
      int r1 = tree.first_true_from_left([&](int x) { return x >= v; }, l);
      int l_rev = n - l;
      int r2 = n - tree_rev.first_true_from_right([&](int x) { return x >= v; }, l_rev);
      assert(r1 == r2);
      cout << r1 << '\n';
    }
  }
}
