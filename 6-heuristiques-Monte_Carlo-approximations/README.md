# Exercice 1: Diamètre d'un graphe

Étant donné un graphe non dirigé et non valué, vous voulez connaître son diamètre: la plus grande distance entre 2 noeuds. 
Problème: votre graphe peut être très grand (des millions de noeuds!). 
On ne peut donc pas calculer la valeur ***exacte*** en faisant, par exemple, un BFS depuis chaque noeud... 

On va donc calculer une valeur ***approchée***: une borne inférieure. Cf le cours -- pour ceux qui n'ont pas écouté, demandez-moi. 

Vous allez notamment réutiliser l'implémentation de graphe du TD1 et le BFS du TD2, qui sont dans test.tar.gz.


***Implémentez*** dans un fichier diam1.cc la fonction DiametreLB() décrite dans le fichier diam1.h:

```
#ifndef __DIAM1_H
#define __DIAM1_H

#include <utility>
#include "ugraph.h"

using namespace std;

// Étant donné un graphe, cette fonction trouve 2 noeuds dont la distance
// (la longueur du plus court chemin entre ces 2 noeuds) est la plus grande
// possible: cela représentera une borne inférieure du diamètre.
//
// ATTENTION:
// Votre algorithme devra tourner en un temps maximal imparti par graphe:
// Tmax = 50ms + (M+N)*1µs, où M est le nombre d'arêtes et N de noeuds.
// Ça correspond a du O(M+N).
// Par exemple, si M = 10M (10 millions), N = 1M (1million), Tmax = 11.05s.
//
// Ensuite, le score dépendra uniquement du diamètre obtenu: plus il est
// grand, meilleur sera votre score.
// Mais si le temps dépasse (sur ma machine!), le score sera 0: gardez une
// bonne marge!
pair<int, int> DiametreLB(const UndirectedGraph& graph);

#endif  // __DIAM1_H
```

Test:
tar xf test.tar.gz
make diam1


![alt text](https://raw.githubusercontent.com/yannistannier/optimisation-combinatoire/master/6-heuristiques-Monte_Carlo-approximations/diametre.png)


***Implémentez*** dans un fichier diam2.cc la fonction DiametreUB() décrite dans le fichier diam2.h:

```
#ifndef __DIAM2_H
#define __DIAM2_H

#include <vector>
#include "ugraph.h"

using namespace std;

// Étant donné un graphe, cette fonction renvoie soit:
// - un noeud (donc, un vector<int> avec un seul élément) "central",
//   qui minimise le "rayon" du graphe pour ce centre: le "rayon" est
//   la plus grande distance à un autre noeud du graphe.
// - une sous-clique centrale, c'est-à-dire un sous-ensemble de noeuds
//   tels qu'ils soient tous directement connectés entre eux par une
//   arête, et tel que le "rayon" soit minimal pour ce "multi-centre".
//
// Dans les 2 cas, on peut déduire une borne supérieure sur le diamètre
// du graphe:
// - si on a renvoyé un noeud de rayon R: Diamètre <= 2*R
// - si on a renvoyé une sous-clique de rayon R: Diamètre <= 2*R+1
//
// Pour faire simple, vous pourrez vous limiter à renvoyer un simple noeud.
// Pour être un peu meilleur, vous pourrez renvoyer une arête (2 noeuds
// liés par une arête). Voire une sous-clique...
//
// ATTENTION:
// Même temps maximal imparti que pour l'exercice précédent.
// Le score sera fonction de la borne sup du diamètre (voire formule en haut):
// plus elle est petite, meilleur sera le score.
vector<int> DiametreUB(const UndirectedGraph& graph);

#endif  // __DIAM2_H
```

Test: make diam2 




# Exercice 2: Minimum Feedback Arc Set

Un gérant de club de karaté est obsédé par le classement de ses élèves. Il dispose d'un historique des combats. 
Il considère que A "gagne" contre B si A et B se sont combattues au moins une fois, et si A a remporté la majorité des combats contre B. 
Intuitivement, il se dit que si A gagne contre B, et B contre C, alors A gagne contre C. 
Mais c'est faux en pratique: parfois, C gagne contre A. 

Comment établir un classement? 
Une solution est de chercher un Feedback Arc Set de taille minimale dans le graphe dirigé des "X gagne contre Y", 
c'est-à-dire un ensemble d'arcs le plus petit possible tel que si on les enlève, le graphe devient acyclique: 
on pourra alors trier les élèves en utilisant, par exemple, un ordre topologique. 

***Implémentez*** dans un fichier fas.cc la fonction MaxDAG() décrite dans le fichier fas.h:

```
#ifndef __FAS_H
#define __FAS_H

#include "graph.h"

// Renvoie un sous-graphe de "graph" (même noeuds, mais un sous-ensemble des
// arcs), acyclique, et avec le plus d'arcs possible.
// Comme les exercices précédents, vous aurez un temps maximal par graphe,
// un peu supérieur cette fois:
// Tmax = 50ms + (M+N)*10µs
//
// Le score sera:
// - 0 si la sortie est incorrecte, ne serait-ce que sur un ensemble de test.
// - si toutes les sorties sont correctes, la somme des scores:
//   - chaque score sera de 0 si le temps max est dépassé
//   - sinon il dépendra du nombre d'arcs du graphe que vous renvoyez.
DirectedGraph MaxDAG(const DirectedGraph& graph);

#endif  // __FAS_H
```

Test: make fas 

![alt text](https://raw.githubusercontent.com/yannistannier/optimisation-combinatoire/master/6-heuristiques-Monte_Carlo-approximations/dag.svg)


# Exercice 3: TSP (Traveling Salesman Problem)

On s'intéresse au problème du ***voyageur de commerce***, dans sa version "tour": on veut revenir au point de départ. 

D'excellentes idées d'approximation, toutes en O(N² polylog(N)), sont décrites sur cette page (copie locale), de la plus simple à la plus compliquée (à la louche). 
Attention: parfois il n'est pas trivial de trouver comment obtenir cette complexité: un algo mal implementé peut facilement être en O(N³), ce qui sera trop lent! 

***Implémentez*** dans un fichier tsp.cc la fonction ```TSP()``` décrite dans le fichier tsp.h:

Test: make tsp 
