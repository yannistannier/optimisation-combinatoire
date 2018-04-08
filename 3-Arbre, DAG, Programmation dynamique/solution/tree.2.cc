#include "tree.2.h"

int Height(const vector<vector<int>>& enfants, int node) {
  if (enfants[node].empty()) return 0;
  int maxi = 0;
  for (int e : enfants[node]) {
    maxi = max(maxi, Height(enfants, e));
  }
  return maxi + 1;
}
