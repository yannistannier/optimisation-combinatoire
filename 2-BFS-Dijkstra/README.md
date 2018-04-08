# Exercice 1: BFS

### 1. Reprenez les fichiers graph.h, graph.cc, ugraph.h et ugraph.cc faits lors du dernier TD (corrigés) 
Implémentez dans un fichier bfs.1.cc la fonction BFS() décrite dans le fichier bfs.1.h:

```
#include "ugraph.h"

// Runs a Breadth-First-Search on the graph, starting from node "src".
// See https://en.wikipedia.org/wiki/Breadth-first_search .
// Returns a vector of size N (N is the number of nodes of the
// graph) representing the "parent" tree: parent[i] is the parent of
// node #i in the BFS tree. The parent of "src" is itself, and the
// parent of a node that wasn't reached by the BFS exploration is -1.
vector<int> BFS(const UndirectedGraph& graph, int src);
```

La complexité devra être O(M + N), où M est le nombre d'arcs et N le nombre de noeuds. 

Test:
```
tar xf test.tar.gz
make bfs.1
```


### 2. Implémentez la fonction GetBfsDistances() décrite dans le fichier bfs.2.h:

```
#include <vector>
using std::vector;

// Extracts the distances of each node in the given BFS tree, which
// is the returned format described in bfs.1.h
// Eg. in the following tree, whose root is "2":
//
//         .---- 4
//         v
//   2 <-- 3 <-- 1
//   ^
//   '---- 0 <-- 5
//
// The bfs tree is represented by the following 'parent' vector:
// [2, 3, 2, 2, 3, 0]
// And the distance vector should be:
// [1, 2, 0, 1, 2, 2]
//
// If a node was not reached by the BFS, its parent is -1, and its distance
// should also be -1.
vector<int> GetBfsDistances(const vector<int>& parents);
```

Test: make bfs.2 


### 3. Implémentez la fonction GetShortestPathFromRootedTree() décrite dans le fichier bfs.3.h:

```
#include <vector>
using std::vector;

// Returns the shortest path, from the source of a BFS to the given target node.
// The argument is the target node and the BFS "parent" tree.
// If the target node was not reached by the BFS, the returned path should be
// empty.
// Example: using the same example as in bfs.2.h, with BFS 'parent' tree:
// [2, 3, 2, 2, 3, 0]
// Then:
// - the shortest path to node #4 should be: [2, 3, 4]
// - the shortest path to node #0 should be: [2, 0]
// - the shortest path to node #5 should be: [2, 0, 5]
// - the shortest path to node #2 should be: [2]
vector<int> GetShortestPathFromRootedTree(const vector<int>& parent, int target);
```

Test: make bfs.3


# Exercice 2: Dijkstra

### 1. Copiez graph.h et graph.cc dans vgraph.h et vgraph.cc, et modifiez la fonction AddArc() pour qu'elle prenne un argument supplémentaire: double length. 
Modifiez également la fonction Neighbors() pour qu'elle renvoie un const vector<pair<int, double>>&. 

Test: make vgraph 


### 2. (**) Implémentez la fonction Dijkstra() décrite dans le fichier dijkstra.h:

```
#include "vgraph.h"
// Runs a Dijkstra search on the graph, starting from node "src".
// See https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm .
// Returns the same "parent" vector as BFS() in bfs.1.h.
vector<int> Dijkstra(const DirectedGraph& graph, int src);
```

On utilisera priority_queue<> sur une struct qu'on définira, qui correspond à un noeud du graph associé à sa distance depuis la source, assorti d'un opérateur < adapté à ce qu'on en veut pour la priority_queue. 
La complexité devra être O(N + M log(M)). 

Test: make dijkstra 
