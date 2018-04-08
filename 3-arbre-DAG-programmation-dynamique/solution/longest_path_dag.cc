#include "longest_path_dag.h"
#include "toposort.h"

int LongestPathInDag(const DirectedGraph& graph, vector<int>& poids) {
  vector<int> max_path(graph.NumNodes(), 0);
  int global_max = -1;
  for (int node : TopologicalSort(graph)) {
    int max_child_path = 0;
    for (int child : graph.Neighbors(node)) {
      max_child_path = max(max_child_path, max_path[child]);
    }
    max_path[node] = poids[node] + max_child_path;
    global_max = max(global_max, max_path[node]);
  }
  return global_max;
}
