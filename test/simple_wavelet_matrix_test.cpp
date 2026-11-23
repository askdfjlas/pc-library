#include "data_structures/simple_wavelet_matrix.hpp"
#include "starter.hpp"

// https://judge.yosupo.jp/problem/range_kth_smallest
// 189ms
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  FOR(i,n) cin >> a[i];
  SimpleWaveletMatrix w(a);
  FOR(_,m) {
    int l, r, k;
    cin >> l >> r >> k;
    r--; k++;
    cout << w.kth_smallest(l, r, k) << '\n';
  }
}
