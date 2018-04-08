#include "sac2.h"
#include <algorithm>

double Sac2(int C, const vector<int>& p, const vector<double>& v) {
  int n = p.size();  // Num elements.
  vector<int> indices;
  for (int i = 0; i < n; ++i) indices.push_back(i);
  std::sort(indices.begin(), indices.end(),
            [&](int i, int j) {
              if (p[j] == 0) return false;
              if (p[i] == 0) return true;
              return v[i] * p[j] > v[j] * p[i];
            });
  double val = 0;
  for (int i : indices) {
    if (p[i] <= C) {
      C -= p[i];
      val += v[i];
    } else {
      val += v[i] * double(C) / p[i];
      break;
    }
  }
  return val;
}
