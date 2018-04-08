### Exercice 1: Graphe dirigé

1. Complétez le fichier graph.h et implémentez-le dans un fichier graph.cc! 

**Attention:** chaque méthode devra avoir une complexité O(1).

```
// A directed graph is a set of nodes, linked by arcs. Arcs are directed: they
// go from a node to another node.
// In this implementation, each node is an integer in [0, num_nodes-1].
//
// For example, the following graph:
//
//  0 <--- 1 <--> 3 ---> 4
//  ^      |       \     ^
//  |      v        `----'
//  '----- 2
//
// Can be obtained by:
//   DirectedGraph g(5);
//   g.AddArc(1, 0);
//   g.AddArc(1, 3);
//   g.AddArc(3, 1);
//   g.AddArc(2, 0);
//   g.AddArc(1, 2);
//   g.AddArc(3, 4);
//   g.AddArc(3, 4);
//
class DirectedGraph {
 public:
  // At construction, the graph has no arcs.
  explicit DirectedGraph(int num_nodes);

  int NumNodes() const;

  void AddArc(int from, int to);

  // Returns the number of arcs originating from "node".
  // In the example above, OutDegree(1) = 3, OutDegree(4) = 0.
  int OutDegree(int node) const;

  // Returns all the destination nodes that were added with arcs
  // originating from "node".
  // In the example above, Neighbors(1) is {0, 2, 3} and Neighbors(2) is {0}.
  const vector<int>& Neighbors(int node) const;

 private:
  // TODO
};

```

**Testez** votre code:
```
tar xf test.tar.gz
make 1
```

2. Ajoutez une fonction qui renvoie le nombre d'arcs: int NumArcs() const 

Comment faire pour qu'elle tourne en O(1)? Vous pourrez adapter la classe, mais attention, la complexité de toutes les opérations doit rester O(1). 

**Test:** make 2 


3. Ajoutez une fonction void MakeSimple() qui éliminera toutes les boucles et multi-arcs du graphe, en le rendant donc simple. 
Elle devra fonctionner en O(N log N), voire en O(N) si vous y arrivez. 

**Test:** make 3 


### Exercice 2: Graphe non dirigé, composantes connexes

1. Complétez le fichier ugraph.h et implémentez-le dans un fichier ugraph.cc! 

Attention: chaque méthode devra avoir une complexité O(1).

```
#include "graph.h"

// An undirected graph is just like a directed graph, but arcs are called
// "edges" and they don't have a direction: an edge (a, b) is present both
// in the adjacency list of a and the adjacency list of b.
class UndirectedGraph {
 public:
  explicit UndirectedGraph(int num_nodes);

  void AddEdge(int a, int b);

  int NumNodes() const;
  int NumEdges() const;
  int Degree(int node) const;
  const vector<int>& Neighbors(int node) const;

 private:
  // TODO
  // HINT: Use a DirectedGraph where you store each edge (a, b) as two arcs
  // a->b and b->a !
};

```

Test:
make u1


2. Ajoutez une fonction vector<int> GetNodesConnectedTo(int node) qui renvoie les noeuds qui sont dans la même composante connexe que node 

Test: make u2 


3. Ajoutez une fonction vector<vector<int>> ConnectedComponents() qui renvoie toutes les composantes connexes du graphes, dans un ordre quelquonque. 

Test: make u3 

4. [*] Implémentez la fonction décrite dans triangles.h:
```
#include "ugraph.h"

// Returns the number of sorted triples of nodes i<j<k such that
// (i,j), (j,k) and (k,i) are edges of the graph.
int NumTriangles(const UndirectedGraph& graph);
```

Essayez d'obtenir une complexite meilleure que O(N3). 
Indice: vous pouvez par exemple ajouter une fonction void SortAdjacencyList() dans les classes DirectedGraph et UndirectedGraph pour trier les listes d'adjacence sans véritablement "changer" le graphe. Cela peut vous aider à trouver un algorithme plus efficace. 

Test: make u4 

