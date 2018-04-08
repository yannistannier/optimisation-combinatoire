# Exercice 1: Sac à dos

Vous avez un sac à dos de capacité C (en poids) et une liste de n objets de poids p[0], p[1], ... p[n-1]. 
Votre but: mettre le plus possible d'objets dans votre sac à dos, sans dépasser la capacité. 

***Implémentez*** dans un fichier sac1.cc la fonction Sac1() décrite dans le fichier sac1.h:

```
#ifndef __SAC1_H
#define __SAC1_H

#include <vector>
using namespace std;

// On a un sac à dos de capacité C, et des objets de poids p[0], p[1], ...
// On veut selectionner le plus grand nombre possible d'objets tel que
// la somme de leurs poids soit <= C.
// Cette fonction renvoie ce nombre maximal d'objets.
//
// EXEMPLE: C=12, p=[4, 7, 2, 5, 5, 1, 10]
//          -> renvoie 4 car on peut mettre 4 objets au maximum
//             (de poids 4, 2, 5, 1: 4+2+5+1 = 12)
int Sac1(int C, const vector<int>& p);

#endif  // __SAC1_H
```

Test:
```
tar xf test.tar.gz
make sac1
```



À présent, les objets sont ***valués*** (v[0], v[1], ...) et peuvent être pris de manière fractionnaire: 
pour chaque object, vous pouvez choisir d'en mettre une fraction (un nombre dans [0, 1]) dans le sac à dos: 
vous gagnerez la fraction correspondante de sa valeur, tout en occupant la fraction correspondante de son poids. 

Quels objets (avec quelles fractions) choisir pour maximiser la valeur transportée dans le sac à dos? 

***Implémentez*** dans un fichier sac2.cc la fonction ```Sac2()``` décrite dans le fichier sac2.h:

```
#ifndef __SAC2_H
#define __SAC2_H

#include <vector>
using namespace std;

// On a un sac à dos de capacité C, et des objets de poids p[0], p[1], ...
// et de valeurs v[0], v[1], ...
// Cette fonction renvoie la valeur maximale que l'on peut collecter dans le sac
// à dos, en supposant qu'on peut mettre les objets de manière fractionnaire.
//
// EXEMPLE: C=12, p=[4, 7, 2, 5, 5, 1, 10], v=[3.1, 99, 0.1, 0.2, 6.6, 0.4, 111]
// -> Doit renvoyer 154.5. Explication:
//    la solution optimale est de prendre l'objet #1 en entier (poids 7, valeur 99)
//    et la moitié de l'objet #6 (poids 10, valeur 111).
//    On a bien un poids total de 7*1 + 10*0.5 = 12.
//    On obtient une valeur totale de 99*1 + 111*0.5 = 154.5
double Sac2(int C, const vector<int>& p, const vector<double>& v);

#endif  // __SAC2_H
```

Test: make sac2 



# Exercice 2: Arbre couvrant minimal

***Implémentez*** dans un fichier prim.cc l'algorithme de Prim pour trouver un arbre couvrant minimal: ```Prim()```, décrite dans le fichier prim.h:


```
#ifndef __PRIM_H
#define __PRIM_H

#include <vector>
using namespace std;

// Renvoie le poids de l'arbre couvrant minimal pour le graphe valué donné:
// N est le nombre de sommets, et "edges" liste toutes les arêtes du graphe,
// avec leur poids.
//
// EXEMPLE: N = 4, edges = [{0, 1, 23}, {1, 3, 13}, {2, 1, 6}, {3, 2, 11}, {0, 2, 41}]
//
//    .--[23]--1--[13]--.      Les noeuds sont 0,1,2,3.
//  .´         |         `.    Les poids des arêtes sont entre [ ].
// 0          [6]          3
//  `.         |         .´    Arbre couvrant minimal: 23 + 6 + 11 = 40.
//    `--[41]--2--[11]--´
//
struct Edge {
  int node1;
  int node2;
  int weight;
};
int Prim(int N, const vector<Edge>& edges);

#endif  // __PRIM_H
```

Test: make prim 


# Exercice 3: Coloration de sommets dans un graphe

Vous êtes à ma place, et devez donner un devoir à la maison à vos étudiants. 
Problème: ils copient entre eux. 
Vous êtes prêts à préparer plusieurs versions de votre devoir: 2 étudiants ayant 2 versions différentes ne pourront pas copier entre eux. 
Vous connaissez également le réseau social des étudiants: 2 étudiants essaieront de copier entre eux seulement s'ils sont amis dans ce réseau (directement reliés).
 
Comment faire pour donner une version du devoir à chacun, en minimisant le nombre total de versions, et en ne donnant jamais la même version à 2 amis? 

***Implémentez*** dans un fichier color.cc la fonction ```Color()```, décrite dans le fichier color.h:

```
#ifndef __COLOR_H
#define __COLOR_H

#include <vector>
#include "ugraph.h"  // Vous l'avez: il était dans test.tar.gz.

using namespace std;

// Étant donné un graph non dirigé, renvoie un coloriage utilisant
// aussi peu de couleurs que possible.
// Entrée: le graphe non dirigé.
// Valeur de retour: le nombre de couleur C de votre coloriage.
// Sortie: "color" doit contenir autant d'élément que le nombre de noeuds
//         du graphe: color[i] sera la couleur du noeud #i.
//         color[i] doit etre entre 0 et C-1, et deux noeuds ayant une
//         arête en commun ne peuvent pas avoir la même couleur.
//
// NOTE: On attends pas un algorithme optimal (NP complet!), mais votre
// heuristique devra etre aussi "bonne" que possible.
int Color(const UndirectedGraph& graph,
          vector<int>* color);  // La sortie. N'oubliez pas de la remplir!

#endif  // __COLOR_H
```

Test: make color 
