#ifndef KMP_HPP
#define KMP_HPP

#include "starter.hpp"

vector<int> compute_lps(string pat) {
  int n = pat.length(), j = 0;
  vector<int> lps(n);
  for(int i = 1; i < n; i++) {
    if(pat[i] == pat[j] || j == 0) {
      if(pat[i] == pat[j]) j++;
      lps[i] = j;
    }
    else {
      j = lps[j - 1];
      i--;
    }
  }
  return lps;
}

vector<int> kmp(string search, string pat) {
  vector<int> res, lps = compute_lps(pat);
  int i = 0, j = 0;
  while(i < (int)search.length()) {
    if(search[i] == pat[j]) {
      i++;
      j++;
      if(j == (int)pat.length()) {
        res.push_back(i - j);
        j = lps[j - 1];
      }
    }
    else {
      if(j != 0) j = lps[j - 1];
      else i++;
    }
  }
  return res;
}

#endif