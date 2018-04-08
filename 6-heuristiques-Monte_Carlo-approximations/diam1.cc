#include "bfs.1.h"
#include "bfs.2.h"
#include "bfs.3.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

pair<int, int> DiametreLB(const UndirectedGraph& graph) {
  // On utilisera 50% du temps limite (pour garder une bonne marge).
  const double tmax = 1e-6 * (graph.NumNodes() + graph.NumEdges()) + 50e-3;
  const clock_t deadline = clock() + 0.4 * CLOCKS_PER_SEC * tmax;

  int max_d = -1;
  pair<int, int> best = {0, 0};

  // Algorithme: on alterne 2 et 3 bfs, au hasard, en prenant les sources
  // au hasard. 
  const int n = graph.NumNodes();
  do {
    // Premier BFS.
    int src = random() % n;
    vector<int> distances = GetBfsDistances(BFS(graph, src));
    // Ensuite on fera un, voire deux BFS.
    const int num_bfs = 2 + (random() % 2);
    for (int bfs = 1; bfs < num_bfs; ++bfs) {
      // On recupere les noeuds les plus eloignés du BFS...
      vector<int> farthest;
      int dist_max = -1;
      for (int i = 0; i < n; ++i) {
        if (distances[i] > dist_max) {
          farthest = {i};
          dist_max = distances[i];
        } else if (distances[i] == dist_max) {
          farthest.push_back(i);
        }
      }
      // Et on en choisit un au hasard comme prochaine source.
      src = farthest[random() % farthest.size()];
      distances = GetBfsDistances(BFS(graph, src));
    }
    // Une fois fini, on récupère la paire (src, node) qui realise le max.
    int node = 0;
    for (int i = 1; i < n; ++i) {
      if (distances[i] > distances[node]) node = i;
    }
    // Et on met à jour notre diamètre.
    if (distances[node] > max_d) {
      max_d = distances[node];
      best = {src, node};
    }
  } while (clock() < deadline);
  return best;
}
