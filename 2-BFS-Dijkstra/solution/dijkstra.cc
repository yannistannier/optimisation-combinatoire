#include "dijkstra.h"
#include <limits>
#include <queue>

vector<int> Dijkstra(const DirectedGraph& graph, int src) {
  const int n = graph.NumNodes();
  vector<int> parent(n, -1);
  parent[src] = src;
  vector<double> dist(n, std::numeric_limits<double>::infinity());
  dist[src] = 0.0;
  struct NodeDist {
    int node;
    double dist;
    bool operator<(const NodeDist& other) const { return dist < other.dist; }
  };
  std::priority_queue<NodeDist> pq;
  pq.push({src, 0.0});
  while (!pq.empty()) {
    const auto top = pq.top();
    pq.pop();
    if (top.dist > dist[top.node]) continue;
    for (const auto& p : graph.Neighbors(top.node)) {
      const int neigh = p.first;
      const double d = p.second + top.dist;
      if (d < dist[neigh]) {
        dist[neigh] = d;
        parent[neigh] = top.node;
        pq.push({neigh, d});
      }
    }
  }
  return parent;
}
