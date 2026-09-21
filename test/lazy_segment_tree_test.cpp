#include "data_structures/segment_tree/frequent_lazy_segment_trees.hpp"
#include "starter.hpp"

using segtree = frequent_lazy_segment_trees::SMMAddInt;
using smm = frequent_lazy_segment_trees::SMM;

// https://atcoder.jp/contests/practice2/tasks/practice2_j
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n, q;
  cin >> n >> q;
  vector<smm> a(n + 1);
  FORR(i,1,n) {
    int x;
    cin >> x;
    a[i] = x;
  }
  segtree tree(a);
  reverse(a.begin(), a.end());
  segtree tree_rev(a);  // redundant but used to test [first_true_from_right]
  FOR(_,q) {
    // perform useless ops for testing
    vector<tuple<int,int,int>> ops;
    FOR(__,10) {
      int l = rng() % n, r = rng() % n, v = (rng() % n) - 100;
      if(l > r) swap(l, r);
      ops.push_back({l, r, v});
      tree.apply(l, r, v);
    }
    shuffle(ops.begin(), ops.end(), rng);
    for(auto [l, r, v]: ops)
      tree.apply(l, r, -v);
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
      int r1 = tree.prod(l, r).max_;
      int l_rev = n - l, r_rev = n - r;
      int r2 = tree_rev.prod(r_rev, l_rev).max_;
      assert(r1 == r2);
      cout << r1 << '\n';
    }
    else {
      int l, v;
      cin >> l >> v;
      int r1 = tree.first_true_from_left([&](smm x) { return x.max_ >= v; }, l);
      int l_rev = n - l;
      int r2 = n - tree_rev.first_true_from_right([&](smm x) { return x.max_ >= v; }, l_rev);
      assert(r1 == r2);
      cout << r1 << '\n';
    }
  }
}
