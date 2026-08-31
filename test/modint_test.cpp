#include "data_structures/modint.hpp"
#include "starter.hpp"

using mint = Mint<998244353>;

int main() {
  mint x;
  cin >> x;
  cout << x << ' ' << x.inv() << '\n';
  
  x *= 5;
  cout << x << '\n';
  x /= 5; 
  cout << x << '\n';
 
  mint y = 69;
  FOR(_,70) y--;
  assert(y == 998244352);
  y += 5;
  assert(y == 4);
}