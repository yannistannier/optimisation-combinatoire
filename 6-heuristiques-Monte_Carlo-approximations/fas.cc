#include "fas.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

// Cette structure de donnée permet de maintenir les composantes connexes
// dynamiquement, en temps quasi-linéaire (voir "Union-find" ou
// "Disjoint sets" sur Google). L'implémentation est en bas du fichier.
class UnionFind {
 public:
  explicit UnionFind(int num_nodes);

  // Returns true if "a" and "b" have been connected by this call,
  // and "false" if they were already connected.
  bool AddEdge(int a, int b);

  int GetRoot(int node);

 private:
  vector<int> parent_;
  vector<int> depth_;
};

// Cette fonction auxilliaire permet de rajouter des arcs, copié d'un graphe
// g_origin, à un graphe g_target: on itère sur les arcs A->B de g_origin, et
// si A et B ne sont pas connectés (sans prendre en compte la direction des
// arcs) dans g_target, on l'ajoute. Cela nous assure qu'on ne crée pas de
// cycle, et aussi qu'on ajoute pas des arcs qui y etaient deja.
// NOTE: On pourrait être plus "agressif", et autoriser la création de A->B
// quand A et B sont connectés, mais qu'il n'existe pas de chemin dirigié
// B->...->A, mais ce n'est pas facile de faire cela en temps linéaire.
void CopyArcsUntilWeaklyConnected(const DirectedGraph& g_origin,
                                  DirectedGraph* g_target) {
  if (g_origin.NumNodes() != g_target->NumNodes()) {
    cerr << "BUG! RandomlyAddArcsUntilWeaklyConnected() called on graphs"
         << " with different sizes!" << endl;
    exit(1);
  }
  const int n = g_target->NumNodes();
  UnionFind uf(n);
  for (int a = 0; a < n; ++a) {
    for (int b : g_target->Neighbors(a)) {
      uf.AddEdge(a, b);
    }
  }
  for (int a = 0; a < n; ++a) {
    for (int b : g_origin.Neighbors(a)) {
      if (uf.AddEdge(a, b)) g_target->AddArc(a, b);
    }
  }
}

DirectedGraph MaxDAG(const DirectedGraph& graph) {
  // Cas speciaux.
  const int n = graph.NumNodes();
  if (graph.NumArcs() == 0) return DirectedGraph(n);

  // On utilisera 50% du temps limite (pour garder une bonne marge).
  const double tmax = 10e-6 * (graph.NumNodes() + graph.NumArcs()) + 50e-3;
  const clock_t deadline = clock() + 0.4 * CLOCKS_PER_SEC * tmax;

  // On crée une permutation des noeuds (initialiement: l'identité).
  vector<int> order;
  for (int i = 0; i < n; ++i) order.push_back(i);

  DirectedGraph max_graph(n);
  while (clock() < deadline) {
    // On permute aléatoirement les noeuds (Google -> 'random_shuffle c++').
    random_shuffle(order.begin(), order.end());

    // On crée les 2 sous-graphes en distribuant les arcs de "graph" soit
    // dans l'un, soit dans l'autre (selon l'ordre qu'on vient de tirer).
    DirectedGraph g0(n);
    DirectedGraph g1(n);
    for (int a = 0; a < n; ++a) {
      for (int b : graph.Neighbors(a)) {
        if (order[a] > order[b]) {
          g0.AddArc(a, b);
        } else if (order[a] < order[b]) {
          g1.AddArc(a, b);
        }
      }
    }

    // Ensuite on "complète" chaque sous-graphe, sans créer de cycle.
    CopyArcsUntilWeaklyConnected(graph, &g0);
    CopyArcsUntilWeaklyConnected(graph, &g1);

    // Si le plus grand des 2 sous-graphes est plus grand que notre
    // sous-graphe max actuel, on le garde.
    if (g0.NumArcs() > g1.NumArcs()) {
      if (g0.NumArcs() > max_graph.NumArcs()) max_graph = g0;
    } else {
      if (g1.NumArcs() > max_graph.NumArcs()) max_graph = g1;
    }
  }
  return max_graph;
}

// Implementation de la class UnionFind.
UnionFind::UnionFind(int num_nodes)
  : parent_(num_nodes, -1), depth_(num_nodes, 1) {
  for (int i = 0; i < parent_.size(); ++i) parent_[i] = i;
}

bool UnionFind::AddEdge(int a, int b) {
  const int ra = GetRoot(a);
  const int rb = GetRoot(b);
  if (ra == rb) return false;  // Already connected.
  if (depth_[ra] > depth_[rb]) {
    parent_[rb] = ra;
  } else {
    parent_[ra] = rb;
  }
  return true;
}

int UnionFind::GetRoot(int a) {
  int r = a;
  while (r != parent_[r]) r = parent_[r];
  const int root = r;
  for (int r = a; r != root; ) {
    const int p = parent_[r];
    parent_[r] = root;
    r = p;
  }
  return root;
}
