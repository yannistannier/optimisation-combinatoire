# Installation de or-tools

Dans cette exo on va utiliser le package open-source or-tools de Google (outils d'Optimisation Combinatoire). 
Allez sur la page de or-tools (https://developers.google.com/optimization/), et téléchargez la version pour Ubuntu 16. 
Extrayez le contenu, puis installez-le et créez un repertoire td7 a l'intérieur

```
tar xf or-tools_Ubuntu-16.04-64bit_v6.4.4495.tar.gz
cd or-tools_Ubuntu-16.04-64bit_v6.4.4495
make -j 4 all
make test_cc
mkdir td7
cd td7
// copier test.tar.gz ici
tar xf test.tar.gz
```

Faites le reste de l'exo dans ce repertoire!

***Problèmes d'installation courants & solutions***

1. Si vous obtenez une erreur disant "-lz non trouvé" ("-lz not found" en anglais), faites: sudo apt-get install zlib1g-dev

2. Si le make -j 4 all "freeze", essayez en enlevant le -j 4 dans la commande: make all tout simplement (ce problème arrive notamment aux utilisateurs d'une linux box virtuelle).

3. Si vous avez une version 32bit d'Ubuntu et que d'autres problèmes apparaissent.. Ouch! Essayez peut-etre avec une version plus ancienne d'OR-tools. Si ça ne marche pas, je vous conseille d'utiliser une machine de la salle de TD.

4. Si vous avez un Mac:
- vous téléchargerez, bien sûr, la version Mac. Ca marche a peu près, a condition toutefois de remplacer le Makefile_mac en Makefile dans le repertoire td7 par la version Mac.



# Exercice 1: Menu optimal

***Complétez*** l'implémentation de la fonction ```MenuMoinsCher()``` décrite dans le fichier menu.h et implémentée dans menu.cc:


```
#ifndef __MENU_H
#define __MENU_H

#include <vector>

using std::vector;

// On va résoudre le problème du "menu le plus économique".
// Comme sur les paquets de céréales, on s'intéresse aux apport nutritifs
// de nos ingrédients en calories, protéines, lipides, vitamine B1, etc.
//
// On connait la valeur des Apports Journaliers Recommandés (AJR) pour chacun
// de ces éléments: elle est donnée dans le tableau "ajr".
// Par exemple, si on veut au moins 2000 calories par jour, au moins 60g de
// protéines, etc, on aura ajr = [2000, 60, ...].
//
// On a aussi une liste d'ingrédients: patates, riz, jus d'orange, poulet, etc.
// Pour chaque ingrédient, on connait la valeur de ses apport dans tous les
// éléments (pour 1kg de cet ingrédient), dans le même ordre que la liste "ajr".
// Par exemple, 1kg de patate apporte 2500 calories, 10g de proteines, etc;
// 1kg de riz apporte 4000 calories, 13g de proteines, etc; et ainsi de suite
// pour les autres ingrédients: le tableau "apports_par_ingredient" contiendra
// [[2500, 10, ...],  // 1kg de patates
//  [4000, 13, ...],  // 1kg de riz
//  ... ]             // .. autres ingrédients ..
// 
// Enfin, on a le prix au kg de chaque ingrédient dans "prix_par_ingredient".
// Les ingrédients sont listés dans le même ordre que dans
// "apports_par_ingredient". Par exemple, si 1kg de patate coûte 3.2€, 1kg de
// riz coûte 5.4€, etc, on aura prix_par_ingredient = [3.2, 5.4, ...]. 
//
// Notre but: trouver le menu le moins cher possible pour aujourd'hui! Quels
// ingrédients acheter, et en quelle quantité, pour couvrir *au moins* les AJR
// (on peut avoir 'trop' d'un élément, par exemple trop de calories: ce n'est
// pas grave!)
//
// Cette fonction doit trouver le menu journalier le moins cher, et renvoyer
// les quantités de chaque ingrédient dans ce menu, dans le même ordre que
// "prix_par_ingredient".
// Par exemple si le menu idéal journalier est:
// 0.3kg de patates, 0kg de riz, 0.2kg de jus d'orange, ...
// Le tableau renvoyé sera: [0.3, 0, 0.2, ...].
vector<double> MenuMoinsCher(const vector<double>& ajr,
                             const vector<vector<double>>& apports_par_ingredient,
                             const vector<double>& prix_par_ingredient);

#endif  // __MENU_H
```

Test: make menu



# Exercice 2: Multi-commodity flow


***Complétez*** l'implémentation de la fonction ```BestFlow()``` décrite dans le fichier flow.h et implémentée dans flow.cc:

```
#ifndef __FLOW_H
#define __FLOW_H

#include <vector>

using std::vector;

// Problème de l'affectation de traffic réseau dans un backbone:
// On gère un backbone, qui est un graphe dirigé valué (chaque arc a une
// certaine bande passante).
// Le backbone est donné sous forme de ce graphe: on connait le nombre de
// noeuds N, et on a les arcs valués (from, to, capacity) où "from" et "to"
// sont des noeuds (donc des entiers entre 0 et N-1 inclus) et "capacity"
// est la bande passante, en Gb/s.
// On a également un ensemble de demandes commerciales de traffic, se
// présentant sous la forme (origine, destination, bande passante max,
// prix par Gb/s): cette demande correspond à un client qui veut envoyer
// du traffic du noeud "origine" au noeud "destination" en empruntant notre
// réseau, et qui est prêt a payer un certain prix par Gb/s qu'on lui alloue,
// dans la limite de sa bande passante max.
//
// Quels demandes commerciales doit-on choisir, en quelles quantités?
// Comment router le traffic réseau correspondant?
struct BackboneArc {
  int from;  // Un noeud
  int to;    // Un noeud
  double capacity;  // >= 0
};
struct FlowDemand {
  int src;  // Source: un noeud
  int dst;  // Destination: un noeud
  double demand;  // >= 0
  double price;   // per unit of demand (max profit = demand * price)
};
struct FlowOnArc {
  int arc_index;  // Index dans l'entrée "backbone".
  int demand_index;  // Index dans l'entrée "demands".
  double flow;
};
vector<FlowOnArc> BestFlow(int num_nodes,
                           const vector<BackboneArc>& backbone,
                           const vector<FlowDemand>& demands);

#endif  // __FLOW_H
```

Test: make menu 