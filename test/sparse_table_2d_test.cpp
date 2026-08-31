#include "data_structures/sparse_table_2d.hpp"
#include "starter.hpp"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  vector<vector<int>> test =  {
    {1, 2, 3, 4}, {2, 3, 4, 5}, {9, 9, 9, 9}, {-1, -1, -1, -1}
  };
  
  SparseTable2d<int> st(test);
  SparseTable2d<int,greater<int>> st2(test);
  cout << st.query(0, 3, 0, 3) << ' ' << st.query(2, 2, 2, 2) << '\n';
  cout << st2.query(0, 3, 0, 3) << ' ' << st2.query(3, 3, 3, 3) << '\n';
}
