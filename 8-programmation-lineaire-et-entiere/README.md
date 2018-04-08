# Installation de or-tools

Voir la procédure d'installation dans l'enoncé de l'exo 7. 
Pas besoin de réinstaller si l'installation est encore là. 

Cette fois, on va créer un sous-repertoire "td8" dans or-tools_Ubuntu-16.04-64bit_v6.4.4495, et on travaillera dans ce sous-repertoire:

```
mkdir td8  # En etant dans le repertoire or-tools-BlaBlaBla
cd td8
// Copier test.tar.gz ic
tar xf test.tar.gz
```



# Exercice 1: Multi-commodity flot, version 2

***Reprenez*** l'exercice 2 du dernier TD: flow.h, flow.cc. 
***Téléchargez*** également le nouveau flow2.h, puis renommez flow.cc en flow2.cc et adaptez-le en fonction.

```
#ifndef __FLOW2_H
#define __FLOW2_H

#include "flow.h"

// Come BestFlow() (voir flow.h), mais on ajoute une penalité pour trop
// "remplir" les arcs du backbone: si le taux d'utilisation U d'un arc
// (entre 0 et 1, 0 = pas utilisé, 1 = utilisé à sa limite de capacité)
// est supérieur à x, on paiera une penalité proportionelle à (U-x).
//
// On veut toujours maximiser le gain global, mais en prenant en compte
// la penalité de ces arcs trop remplis.
//
// Exemple:
// - Un backbone avec 4 arcs de capacités 1000, 300, 500, 100.
// - Une solution ou la somme des flots sur ces arcs vaut: 840, 300, 470, 90.
// Si max_free_utilization_ratio=0.9, les arcs en "sur-utilisation" sont les
// 2eme et 3eme arcs. Le 1er est en-dessous du seuil, le dernier est juste au
// seuil. Les coefficients de sur-utilisations des arcs sont: 0, 0.1, 0.04, 0. 
// Si penalt_cost=100, le coût de cette sur-utilisation est de:
// 0.1*penalty_cost + 0.04*penalty_cost.
//
// INDICATIONS:
// On pourra imiter et meme remplacer les contraintes de capacités en
// introduisant des variables de "sur-utilisation", et en adaptant la contrainte
// de capacité avec ces variables.
vector<FlowOnArc> BestFlow2(int num_nodes, const vector<BackboneArc>& backbone,
                            const vector<FlowDemand>& demands,
                            double max_free_utilization_ratio,
                            double penalty_cost);

#endif  // __FLOW2_H
```


Test:
```
tar xf test.tar.gz
make flow2
```


# Exercice 2: Job assignment

Vous gérez un datacenter et vous avez un ensemble de taches à faire tourner sur vos machines. 
***Implémentez*** dans un fichier job.cc la fonction BestJobAssignment() décrite dans job.h. 

***ATTENTION***: comme le modèle s'écrit avec des variables entières, il faut utiliser:
- CBC_MIXED_INTEGER_PROGRAMMING au lieu de GLOP_LINEAR_PROGRAMMING quand on créé le solveur.
- MakeBoolVar(..) ou MakeIntVar(..) quand on créé une variable entière au lieu de MakeVar(..)

```
#ifndef __JOB_H
#define __JOB_H

#include <vector>

using std::vector;

// On veut affecter des tâches (job) à des machines.
// On a un ensemble de machines hétérogènes, et des descriptions de jobs.
// Chaque job utilise une quantité prédéfinie de CPU, RAM et disque de la
// machine sur laquelle il tournera, et chaque machine a une quantité
// prédéfinie des CPU, RAM et disque.
//
// On veut maximiser le nombre de jobs affectés.
//
// Cette fonction doit renvoyer un assignment optimal des jobs à chaque
// machine: l'élement #i sera le numero de machine à laquelle le job #i
// sera affecté, où -1 si on décide de ne pas affecter le job.
struct Resources {
  double cpu;
  double ram;
  double disk;
};
vector<int> BestJobAssignment(const vector<Resources>& jobs,
                              const vector<Resources>& machines);

#endif  // __JOB_H
```

Test: make job 
