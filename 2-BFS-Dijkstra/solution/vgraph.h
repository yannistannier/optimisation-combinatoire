#ifndef DIRECTED_GRAPH_H_
#define DIRECTED_GRAPH_H_

#include <vector>
#include <utility>
using std::vector;
using std::pair;

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
// Can be obtained by calling this on a fresh DirectedGraph:
//   AddArc(1, 0);
//   AddArc(1, 3);
//   AddArc(3, 1);
//   AddArc(2, 0);
//   AddArc(1, 2);
//   AddArc(3, 4);
//   AddArc(3, 4);
//
class DirectedGraph {
 public:
  // At construction, the graph has no arcs.
  explicit DirectedGraph(int num_nodes);

  int NumNodes() const;
  int NumArcs() const;

  void AddArc(int from, int to, double length);

  // Returns the number of arcs originating from "node".
  // In the example above, OutDegree(1) = 3, OutDegree(4) = 0.
  int OutDegree(int node) const;

  // Returns all the destination nodes that were added with arcs
  // originating from "node".
  // In the example above, Neighbors(1) is {0, 2, 3} and Neighbors(2) is {0}.
  const vector<pair<int, double>>& Neighbors(int node) const;

 private:
  void AddNode(int node);

  vector<vector<pair<int, double>>> neighbors_;
  int num_arcs_;
};

#endif  // DIRECTED_GRAPH_H_
