#include "sac1.h"
#include <algorithm>

int Sac1(int C, const vector<int>& p) {
  vector<int> p_sorted = p;
  std::sort(p_sorted.begin(), p_sorted.end());
  int num = 0;
  while (num < p_sorted.size() && p_sorted[num] <= C) {
    C -= p_sorted[num];
    num++;
  }
  return num;
}
