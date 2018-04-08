#include "prim.h"
#include <iostream>
#include <climits>
#include <queue>

using namespace std;

// Rappel: l'algorithme de Prim part d'une composante connexe
// contenant un noeud (on partira du noeud #0), et ajoute pas à pas
// l'arête la plus courte qui relie un noeud dans la composante connexe
// à un autre noeud hors de la composante (ainsi, la composante gagne
// un noeud à chaque étape).
int Prim(int N, const vector<Edge>& edges) {
  if (N <= 1) return 0;
  // On pré-calcule les liste d'adjacence de chaque noeud:
  // adj[i] contiendra la liste des Edges adjacentes au noeud #i.
  vector<vector<const Edge*>> adj(N);
  for (const Edge& e : edges) {
    adj[e.node1].push_back(&e);
    adj[e.node2].push_back(&e);
  }

  // Initialisation: connected[i] sera vrai ssi le noeud #i a déja été
  // ajouté à la composante connexe (celle qu'on augmente)
  vector<bool> connected(N, false);
  int total = 0;  // Poids de l'arbre couvrant minimum

  // File de priorité: on extrait d'abord les noeuds dont la distance
  // à la composante est minimale. Puisque priority_queue<> extrait d'abord
  // les éléments "max", il faut que notre comparateur renvoie 'true'
  // quand i est plus *loin* que j.
  struct NodeDist {
    int node;
    int dist;
    bool operator<(const NodeDist& other) const {
      return dist > other.dist;
    }
  };
  priority_queue<NodeDist> pq;

  // On ajoute le noeud #0.
  pq.push({0, 0});
  // Boucle principale.
  while (!pq.empty()) {
    const int node = pq.top().node;
    const int dist = pq.top().dist;
    pq.pop();
    if (connected[node]) continue;  // On a déjà connecté ce noeud!
    // On a un nouveau noeud. On le connecte et on met à jour le poids total.
    connected[node] = true;
    total += dist;
    // Puis on ajoute tous ses voisins (avec leur distances) a la file.
    for (const Edge* e : adj[node]) {
      const int other = e->node1 == node ? e->node2 : e->node1;
      if (!connected[other]) pq.push({other, e->weight});
    }
  }
  return total;
}
