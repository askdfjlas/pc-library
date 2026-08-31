#include "data_structures/segment_tree/point_segment_tree.hpp"
#include "starter.hpp"

struct SegType {
  ll a; 
  SegType() : SegType(0) {}
  SegType(ll _a) : a(_a) {}
  SegType operator*(SegType t) {
    return SegType(a + t.a);
  }
};

// https://judge.yosupo.jp/problem/point_add_range_sum
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n, q;
  cin >> n >> q;
  vector<SegType> arr(n);
  FOR(i,n) cin >> arr[i].a;

  PointSegmentTree<SegType> tree(arr);
  while(q--) {
    int t, a, b;
    cin >> t >> a >> b;
    if(t == 0) tree.update(a, b);
    else cout << tree.query(a, b - 1).a << '\n';
  }
}
