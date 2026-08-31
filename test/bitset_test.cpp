#include "data_structures/bitset.hpp"
#include "starter.hpp"

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  
  const int BSZ = 8293;
  bitset<BSZ> bs1, bs2;
  Bitset tbs1(BSZ), tbs2(BSZ);
  FOR(i,1000) {
    FOR(j,BSZ) {
      if(rng() % 3 == 0) {
        bs1.set(j, 1);
        tbs1.set(j, 1);
      }
      if(rng() % 3 == 0) {
        bs1.set(j, 0);
        tbs1.set(j, 0);
      }
      if(rng() % 3 == 0) {
        bs1.flip(j);
        tbs1.flip(j);
      }
      if(rng() % 3 == 0) {
        bs2.set(j, 1);
        tbs2.set(j, 1);
      }
      if(rng() % 3 == 0) {
        bs2.set(j, 0);
        tbs2.set(j, 0);
      }
      if(rng() % 3 == 0) {
        bs2.flip(j);
        tbs2.flip(j);
      }
    }
    int rs = (rng() % (2*BSZ)), ls = (rng() % (2*BSZ));
    bs1 <<= rs; tbs1 = (tbs1 >> rs);
    bs2 >>= ls; tbs2 = (tbs2 << ls);
    
    if(rng() % 3 == 0) {
      bs1 = bs1 | bs2;
      tbs1 = tbs1 | tbs2;
    }
    if(rng() % 3 == 0) {
      bs1 = bs1 & bs2;
      tbs1 = tbs2 & tbs1;
    }
    if(rng() % 3 == 0) {
      bs2 = bs2 ^ bs1;
      tbs2 = tbs1 ^ tbs2;
    }
    if(rng() % 3 == 0) {
      bs1 = ~bs1;
      tbs1 = ~tbs1;
    }
    if(rng() % 3 == 0) {
      bs2 = ~bs1;
      tbs2 = ~tbs1;
    }
    
    string s1 = bs1.to_string(), s2 = bs2.to_string();
    string t1 = tbs1.to_string(), t2 = tbs2.to_string();
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    assert(s1 == t1 && s2 == t2);
    
    auto cpy = Bitset(tbs1);
    assert(tbs1 == cpy);
    cpy.flip(rng() % BSZ);
    assert(tbs1 != cpy);
    
    assert((int)bs1.count() == tbs1.count());
    assert((int)bs2.count() == tbs2.count());
  }
}
