#include "data_structures/fenwick_tree.hpp"
#include "starter.hpp"

int main() {
  // Testing
  vector<int> test = {-23, 88, 15, 99, 100, 1000, 2323, 3, 0, 895};
  FenwickTree<int> tree = FenwickTree<int>(test);
  
  assert(tree.lower_bound(-23) == 0);
  assert(tree.lower_bound(88) == 3);
  
  // Too lazy rn to turn these into asserts :^)
  cout << tree.prefix_sum(0) << ' ' << tree.prefix_sum(5) << ' ' << tree.prefix_sum(8) << '\n';
  tree.update(0, 100);
  cout << tree.prefix_sum(5) << ' ' << tree.prefix_sum(8) << '\n';
  tree.update(8, -5235);
  cout << tree.prefix_sum(5) << ' ' << tree.prefix_sum(8) << '\n';
}
