#include "data_structures/segment_tree/range_segment_tree.hpp"
#include "starter.hpp"

const int MOD = 998244353;

struct SegType {
  int l, r, a;
  SegType() : SegType(-1, -1, 0) {}
  SegType(int _l, int _r, int _a) : l(_l), r(_r), a(_a) {}
  SegType operator*(SegType t) {
    if(l == -1) return t;
    if(t.l == -1) return *this;
    return SegType(l, t.r, (a + t.a) % MOD);
  }
};

struct SegFn {
  int b, c;
  SegFn() : SegFn(1, 0) {}
  SegFn(int _b, int _c) : b(_b), c(_c) {}
  SegFn operator*(SegFn f) { 
    return SegFn(((ll)b * f.b) % MOD, ((ll)b * f.c + c) % MOD);
  }
  SegType operator*(SegType t) {
    return SegType(t.l, t.r, ((ll)b * t.a + (ll)c * (t.r - t.l + 1)) % MOD);
  }
};

// https://judge.yosupo.jp/problem/range_affine_range_sum
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n, q;
  cin >> n >> q;
  vector<SegType> arr(n);
  FOR(i,n) {
    cin >> arr[i].a;
    arr[i].l = i;
    arr[i].r = i;
  }

  RangeSegmentTree<SegType,SegFn> tree(arr);
  while(q--) {
    int t, l, r, b, c;
    cin >> t >> l >> r;
    if(t == 0) {
      cin >> b >> c;
      tree.update(l, r - 1, SegFn(b, c));
    }
    else {
      cout << tree.query(l, r - 1).a << '\n';
    }
  }
}
