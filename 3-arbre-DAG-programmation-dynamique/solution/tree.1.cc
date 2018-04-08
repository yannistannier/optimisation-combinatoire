#include "tree.1.h"

vector<vector<int>> ParentVectorToChildrenVector(const vector<int>& parent) {
  const int num_nodes = parent.size();
  vector<vector<int>> enfants(num_nodes);
  for (int i = 0; i < num_nodes; ++i) {
    if (parent[i] >= 0) enfants[parent[i]].push_back(i);
  }
  return enfants;
}
