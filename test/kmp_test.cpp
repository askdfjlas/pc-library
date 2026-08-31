#include "algorithms/kmp.hpp"
#include "starter.hpp"

int main() {
  string pat = "aaaa";
  string search = "aaaaaaabaaaa";

  vector<int> pos = kmp(search, pat);
  for(auto p : pos) cout << p << ' ';
  cout << '\n';
}
