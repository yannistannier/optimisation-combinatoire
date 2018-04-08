# Exercice 1: Arbres

### 1. Implémentez dans un fichier ```tree.1.cc``` la fonction ```ParentVectorToChildVector(...)``` décrite dans le fichier tree.1.h:

```
#ifndef __TREE_1_H
#define __TREE_1_H

#include <vector>
using namespace std;

// Entrée: le tableau de parents d'un arbre enraciné (ou d'une forêt d'arbres
// enracinés): parent[i] = -1 si le noeud i est une racine, et sinon c'est
// le noeud parent de i dans l'arbre qui contient i.
//
// Sortie: le tableau des liste d'enfants: l'élément i du tableau de sortie
// est un vector<int> listant tous les enfants du noeud i (il pourra etre
// vide si i n'a pas d'enfants), dans un ordre quelconque.
//
// Exemple:
//
//    .3.     vector<int> parents = [3, 2, 3, -1, 3, 1]  // size()=6 = num nodes
//   .'|'.
//  2  0  4   vector<vector<int>> enfants = [ [],
//  |                                         [5],
//  1                                         [1],
//  |                                         [2, 0, 4],
//  5                                         [],
//                                            [] ]
vector<vector<int>> ParentVectorToChildrenVector(const vector<int>& parent);

#endif  // __TREE_1_H
```

La complexité devra être O(N), où N est le nombre de noeuds de l'arbre (qui est égale à la taille du vector<int> donné en argument). 

Test:
```
tar xf test.tar.gz
make tree.1
```


### 2. Implémentez dans un fichier tree.2.cc la fonction ```Height()``` décrite dans le fichier tree.2.h:

```
#ifndef __TREE_2_H
#define __TREE_2_H

#include <vector>
using namespace std;

// Entrée: un arbre, représenté par son tableau d'enfants (la sortie de la fonction
// faite dans la question précédente), et un noeud X de cet arbre.
//
// Sortie: la hauteur du sous-arbre de X: 0 si X n'a pas d'enfant, 1 si X n'a que des
// enfants qui n'ont eux-mêmes pas d'enfants, etc.
//
// Indice: la fonction pourra être récursive.
// 
// Exemple:
//    .3.     vector<vector<int>> enfants = [ [], [], [1], [2, 0, 4], [] ]
//   .'|'.
//  2  0  4   -> Height(enfants, 0) = 0 ;   Height(enfants, 1) = 0
//  |         -> Height(enfants, 2) = 1 ;   Height(enfants, 3) = 2
//  1         -> Height(enfants, 4) = 0
int Height(const vector<vector<int>>& enfants, int node);

#endif  // __TREE_2_H
```

La complexité devra être O(taille du sous-arbre). 

Test: make tree.2 


### 3. Implémentez dans un fichier tree.3.cc la fonction ```AllHeights()``` décrite dans le fichier tree.3.h:

```
#ifndef __TREE_3_H
#define __TREE_3_H

#include <vector>
using namespace std;

// Entrée: un arbre, représenté par son tableau d'enfants (la sortie de la
// fonction faite dans la question précédente).
//
// Sortie: les hauteurs de tous les noeuds de l'arbre (le tableau des valeurs
// de Height(i) pour tous les noeuds i de 0 à N-1).
//
// Complexité: O(N).
//
// Indice: vous pourrez utiliser une fonction auxilliaire récursive, déclarée
// et définie dans le .cc, qui ressemblera beaucoup à la Height() de la
// question précédente, à la différence qu'elle utilisera la mémorisation.
// 
// Exemple:
//    .3.     vector<vector<int>> enfants = [ [], [], [1], [2, 0, 4], [] ]
//  .' | '.
//  2  0  4   -> AllHeights(enfants) = [0, 0, 1, 2, 0]
//  |
//  1
vector<int> AllHeights(const vector<vector<int>>& enfants);

#endif  // __TREE_3_H
```

La complexité devra être O(N), où N est le nombre de noeuds total. 

Test: make tree.3 



### 4. Implémentez dans un fichier tree.4.cc la fonction ```AllSubtreeSizes()``` décrite dans le fichier tree.4.h:


```
#ifndef __TREE_4_H
#define __TREE_4_H

#include <vector>
using namespace std;

// Exactement comme la question précédente, mais cette fois on calcule pour
// chaque noeud i la taille de son sous-arbre (nombre de noeuds, i inclus, qui
// sont descendants de i).
// 
// Indices: le code ressemble beaucoup à la question précédente.
//
// Exemple:
//    .3.     vector<vector<int>> enfants = [ [], [], [1], [2, 0, 4], [] ]
//  .' | '.
//  2  0  4   -> AllSubtreeSizes(enfants) = [1, 1, 2, 5, 1]
//  |
//  1
vector<int> AllSubtreeSizes(const vector<vector<int>>& enfants);

#endif  // __TREE_4_H
```

La complexité devra être O(N), où N est le nombre de noeuds total. 

Test: make tree.4 



# Exercice 2: DAG

### 1. Implémentez dans un fichier toposort.cc la fonction ```TopologicalSort()``` décrite dans le fichier toposort.h, qui utilise la classe DirectedGraph vue en TD1 pour les graphes dirigés (une implémentation de référence est contenue dans l'archive ```test.tar.gz``` et devrait donc se trouver dans votre repertoire de travail, mais vous pouvez aussi utiliser la vôtre si vous préférez, a condition qu'elle ait exactement la même interface):

```
#ifndef __TOPOSORT_H
#define __TOPOSORT_H

#include "graph.h"
#include <vector>
using namespace std;

// Fait le tri topologique du graphe dirigé donné en argument, et renvoie
// les indices des noeuds triés selon l'ordre topologique: les "feuilles"
// (noeuds n'ayant pas d'arcs sortant) seront plutot vers le début.
// Si le graphe a un cycle (ce n'est donc pas un DAG, il n'y a donc pas
// d'ordre topologique), la fonction devra renvoyer une tableau vide.
//
// A NOTER / INDICES:
// - Plusieurs ordres topologiques différents existent souvent.
// - On pourra précalculer la liste des parents de chaque noeuds (car on
//   ne dispose que de la liste des enfants via le graphe).
// - On pourra pré-calculer le "degré sortant résiduel" de chaque noeud,
//   et initialiser une file FIFO (queue<int> par exemple) qui contiendra
//   tous les noeuds de degré residuel zéro, mise à jour dynamiquement.
// - La complexité devra être O(M) (nombre d'arcs).
//
// IMPORTANT!!! Dans le cours je donnais l'autre convention de valeurs de
// sortie. Ici on renvoie les noeuds triés par ordre topologique. C'est plus
// facile: au lieu de faire (comme dans le cours):
//    int num = 0;                          // Initialisation
//    vector<int> numero(num_nodes, -1);    // Initialisation
//    ...
//    numero[node] = num++;                 // On 'traite' le noeud "node".
//    ...
//    return numero;
// Vous aurez plutot quelquechose de ce genre dans le TD:
//    vector<int> tri;      // Initialisation
//    ...
//    tri.push_back(node);  // On 'traite' le noeud "node"
//    ...
//    return tri;
//
// Exemple:
//
// 2-->5-->6-->7   Plusieurs ordres topologiques valides (liste non exhaustive):
//     ^   |   |    - [4, 0, 7, 6, 5, 1, 2, 3]
//     |   v   v    - [0, 4, 7, 6, 5, 2, 1, 3]
// 3-->1   0   4    - [4, 7, 0, 6, 5, 1, 3, 2]
//
vector<int> TopologicalSort(const DirectedGraph& graph);

#endif  // __TOPOSORT_H
```

Test: make toposort 


### 2. Implémentez dans un fichier longest_path_dag.cc la fonction ```LongestPathInDag()``` écrite dans le fichier longest_path_dag.h:

```
// Entrée: un graphe dirigé et valué: on donne un poids positif à chaque
// noeud dans le tableau "poids".
//
// Sortie: si le graphe est cyclique, renvoyez -1. Sinon, renvoyez la
// somme des poids des noeuds sur le chemin le plus "lourd", i.e. le chemin
// qui maximise la somme des poids de ses noeuds.
//
// Indices: Si vous avez codé TopologicalSort(), vous pourrez l'utiliser pour
// obtenir la réponse relativement facilement. Sinon, pensez à la
// programmation dynamique!
// Dans les 2 cas, il pourra être utile de créer un tableau qui stockera pour
// chaque noeud i le poids du plus lourd chemin partant de i.
//
// Exemple (les poids des noeuds sont mis entre parenthèse)
//
// 2(4)-->5(5)-->6(1)-->7(2)     Le chemin le plus long/lourd est
//        ^      |      |        unique dans cet exemple: c'est
//        |      v      v        2->5->6->0, qui a un poids total de 14.
// 3(2)-->1(1)   0(4)   4(11)
//
int LongestPathInDag(const DirectedGraph& graph, vector<int>& poids);
```

Test: make longest_path_dag 
