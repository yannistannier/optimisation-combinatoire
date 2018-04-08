#include "tree.4.h"

int SubtreeSizeAux(const vector<vector<int>>& enfants, int node, vector<int>& memo) {
  if (memo[node] >= 0) return memo[node];
  int total = 1;
  for (int e : enfants[node]) {
    total += SubtreeSizeAux(enfants, e, memo);
  }
  return memo[node] = total;
}

vector<int> AllSubtreeSizes(const vector<vector<int>>& enfants) {
  const int num_nodes = enfants.size();
  vector<int> sizes(num_nodes, -1);
  for (int node = 0; node < num_nodes; ++node) {
    SubtreeSizeAux(enfants, node, sizes);
  }
  return sizes;
}
