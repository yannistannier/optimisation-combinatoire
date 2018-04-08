#include "color.h"
#include <set>
#include <unordered_set>
using namespace std;

int Color(const UndirectedGraph& graph,
          vector<int>* color) {
  const int N = graph.NumNodes();
  // Cas spécial. Sinon on a besoin d'au moins 1 couleur.
  if (N == 0) {
    color->clear();
    return 0;
  }
  color->assign(N, -1);  // Initialisation.

  vector<unordered_set<int>> neighbor_colors(N);
  // Ordre: on prend le noeud qui a le plus de couleurs differentes voisines.
  // Tie-break: degre max, then node index.
  auto comp = [&neighbor_colors, &graph](int i, int j) {
    if (neighbor_colors[i].size() != neighbor_colors[j].size()) {
      return neighbor_colors[i].size() > neighbor_colors[j].size();
    }
    if (graph.Neighbors(i).size() != graph.Neighbors(j).size()) {
     return graph.Neighbors(i).size() > graph.Neighbors(j).size();
    }
    return i < j;
  };

  // On insere tous les noeuds dans la file de priorité ainsi définie...
  std::set<int, decltype(comp)> pq(comp);
  for (int i = 0; i < N; ++i) pq.insert(i);

  // Et on les extrait un par un.
  int color_max = 0;
  while (!pq.empty()) {
    const int node = *pq.begin();
    pq.erase(pq.begin());
    // On trouve la premiere couleur "c" dispo.
    int c = 0;
    while (neighbor_colors[node].count(c) > 0) c++;
    (*color)[node] = c;
    // On propage l'info aux voisins et on met a jour la couleur max.
    for (const int neighbor : graph.Neighbors(node)) {
      // Petite optim: si le voisin est deja coloré, inutile de le mettre a jour.
      if ((*color)[neighbor] != -1) continue;
      // De même s'il avait déjà la couleur dans sa blacklist.
      if (neighbor_colors[neighbor].count(c) > 0) continue;
      // Il ne faut pas oublier de mettre à jour la position du voisin dans la file
      // de priorité! On le retire de la file de priorité et on le ré-insère après
      // avoir mis à jour sa blacklist.
      pq.erase(neighbor);
      neighbor_colors[neighbor].insert(c);
      pq.insert(neighbor);
    }
    color_max = max(color_max, c);
  }
  // Le nombre de couleurs utilisé est la couleur max + 1.
  return color_max + 1;
}
