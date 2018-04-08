#include "tree.3.h"

int HeightAux(const vector<vector<int>>& enfants, int node, vector<int>& memo) {
  if (memo[node] >= 0) return memo[node];
  if (enfants[node].empty()) return memo[node] = 0;
  int hmax = 0;
  for (int e : enfants[node]) {
    hmax = max(hmax, HeightAux(enfants, e, memo));
  }
  return memo[node] = hmax + 1;
}

vector<int> AllHeights(const vector<vector<int>>& enfants) {
  const int num_nodes = enfants.size();
  vector<int> heights(num_nodes, -1);
  for (int node = 0; node < num_nodes; ++node) {
    HeightAux(enfants, node, heights);
  }
  return heights;
}
