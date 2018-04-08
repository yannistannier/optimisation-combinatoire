# Installation de or-tools

Voir la procédure d'installation dans l'enoncé de l'exo 7. 

Pas besoin de réinstaller si l'installation est encore là. 

Cette fois, on va créer un sous-repertoire "td9" dans or-tools_Ubuntu-16.04-64bit_v6.4.4495, et on travaillera dans ce sous-repertoire:

```
mkdir td9  # En etant dans le repertoire or-tools-BlaBlaBla
cd td9
// copier test.tar.gz ici
tar xf test.tar.gz
```


# Exercice 1: Job assignment


***Reprenez*** l'exercice 2 du TD 8: job.h, job.cc. 
On ajoute à présent des ***contraintes d'exclusivité locale.*** 
Par exemple: "job X, job Y et job Z sont mutuellement exclusif sur la même machine (quelle qu'elle soit)": 
si le job Y tourne sur la machine #4, alors ni job X ni job Z ne pourront tourner sur la machine #4 (mais ils pourront tourner sur une autre machine). 

***Implémentez*** dans un fichier job1.cc (vous pourrez renommer job.cc) la fonction BestJobAssignment1() décrite dans job1.h.

```
#ifndef __JOB1_H
#define __JOB1_H

#include "job.h"

// Comme BestJobAssignment(), mais on a des contraintes d'exclusivités locales:
// pour chaque liste d'exclusivité L dans "local_exclusive",
// cela exprime le fait que 2 jobs ayant des indices dans L ne peuvent être
// placés sur la même machine.
vector<int> BestJobAssignment1(const vector<Resources>& jobs,
                               const vector<Resources>& machines,
                               const vector<vector<int>>& local_exclusive);

#endif  // __JOB1_H
```

Test: make job1 




On revient à la version de base (sans les contraintes d'exclusivité locale), et on ajoute des contraintes de ***dépendence locale.*** 
Par exemple: "Si job X tourne sur une machine, il a besoin de job Y sur la même machine". 
NOTE: Je pourrais vous demander de cumuler ces contraintes avec les précédentes, il n'y aurait aucun problème! Mais ça vous empêcherait de "sauter" une question. 

***Implémentez*** dans un fichier job2.cc (vous pourrez renommer job.cc) la fonction BestJobAssignment1() décrite dans job2.h.

```
#ifndef __JOB2_H
#define __JOB2_H

#include "job.h"

#include <utility>
using std::pair;

// Comme BestJobAssignment1(), mais on a en plus des contraintes de dépendance
// locales: pour chaque paire (A, B) dans "local_dep", job A dépend de job B
// localement, ce qui veut dire que si job A tourne sur une machine, alors
// job B tourne aussi, et sur la meme machine.
vector<int> BestJobAssignment2(const vector<Resources>& jobs,
                               const vector<Resources>& machines,
                               const vector<pair<int, int>>& local_dep);

#endif  // __JOB2_H
```

Test: make job2 




On ajoute à la version de base des ***contraintes d'exclusivité globale.*** 
Par exemple: "Si job X tourne (sur n'importe quelle machine), alors job Y ne peut pas tourner (meme sur une autre machine)". 

***Implémentez*** dans un fichier job3.cc (vous pourrez renommer job.cc) la fonction BestJobAssignment1() décrite dans job3.h.

```
#ifndef __JOB3_H
#define __JOB3_H

#include "job.h"

// Comme BestJobAssignment1(), mais les exclusivités sont globales
// (2 jobs "exclusifs" ne peuvent pas tourner tous les 2, meme sur
//  des machines différentes).
vector<int> BestJobAssignment3(const vector<Resources>& jobs,
                               const vector<Resources>& machines,
                               const vector<vector<int>>& global_exclusive);

#endif  // __JOB3_H
```

Test: make job3 


On ajoute a la version de base des contraintes ***d'inter-dépendance globale. ***
Par exemple: "job X et job Y ont besoin l'un de l'autre, mais peuvent tourner sur des machines différentes. Donc si job X tourne, alors job Y tourne (possiblement sur une autre machine), et vice-versa". 

***Implémentez*** dans un fichier job4.cc (vous pourrez renommer job.cc) la fonction BestJobAssignment1() décrite dans job4.h.

```
#ifndef __JOB4_H
#define __JOB4_H

#include "job.h"

#include <utility>
using std::pair;

// Comme BestJobAssignment2(), mais les dépendances sont bidirectionelles,
// et globales: chaque paire (A, B) dans "global_dep" implique que
// les jobs A et B ne peuvent pas tourner l'un sans l'autre (pas forcément
// sur la même machine).
vector<int> BestJobAssignment4(const vector<Resources>& jobs,
                               const vector<Resources>& machines,
                               const vector<pair<int, int>>& global_dep);

#endif  // __JOB4_H
```

Test: make job4 



# Exercice 2: Too Big For Mip

***Implémentez*** dans un fichier job0.cc la fonction BestJobAssignment0() décrite dans job0.h. 

Indices:
1. Vous pourrez copier-coller le code de job.cc pour avoir la fonction "de base", en le modifiant pour:
	- Ajouter une limite de temps: ```solver.set_time_limit(1000)``` donne au solveur une limite de 1 seconde, par exemple.
	- Prendre en compte les profits
2. Vous devrez sans doute, si vous utilisez les limite de temps, faire attention à la valeur de retour de ```Solve(): MPSolver::OPTIMAL, MPSolver::FEASIBLE,``` etc. Voir lignes 327-335 de linear_solver.h.
3. Vous pourrez essayer de séparer le probleme en sous-problemes

```
#ifndef __JOB0_H
#define __JOB0_H

#include "job.h"

// Comme le BestJobAssignment() original (sans contraintes exotiques),
// mais cette fois:
// 1) Les jobs rapportent un certain "profit", et vous voulez maximiser
//    la somme des profits des jobs assignés.
// 2) Vous devrez etre capables de traiter des problemes
//    de taille beaucoup plus grande
// 3) Vous ne devez pas dépasser 10s de temps de calcul.
// 4) Du coup, vous n'etes pas obligé de renvoyer la solution optimale:
//    votre solution sera jugée en fonction de sa qualité (elle devra
//    bien sûr etre faisable!)
vector<int> BestJobAssignment0(const vector<Resources>& jobs,
                               const vector<double>& profits,
                               const vector<Resources>& machines);

#endif  // __JOB0_H
```

Test: make job0 
