# Exercice 1: Parcelles de culture


Un fermier dispose d'un champ oblong composé de Nx1 parcelles de culture carrées juxtaposées, numérotées 0, ..., N-1. 
Chaque parcelle a des caractéristiques différentes, et le fermier sait que la parcelle #i lui rapportera Gain[i] s'il l'utilise pour faire pousser du maïs. 
Il y a cependant une contrainte: le fermier ne peut jamais utiliser deux parcelles adjacentes. 
Comment peut-il maximiser son gain? 

***Implémentez*** dans un fichier parcel.cc la fonction ```MaxGain()``` décrite dans le fichier parcel.h:

```
#ifndef __PARCEL_H
#define __PARCEL_H

#include <vector>
using namespace std;

// Le gain de cultiver la parcelle #i est gain[i]. Si on cultive la parcelle
// #i, on ne peut pas cultiver la parcelle #i-1 ni la parcelle #i+1.
// Cette fonction renvoie le gain maximum.
//
// EXEMPLE:
// MaxGain([3, 7, 2, 1, 8, 4, 3]) = 18
int MaxGain(const vector<int>& gain);

#endif  // __PARCEL_H
```


On pourra utiliser l'approche récursive avec mémorisation (avec par exemple une fonction MaxGainAux() qui prendrait en argument supplémentaire un tableau de mémorisation et un indice indiquant une partie "déjà traitée"), ou l'approche itérative. 

Test:
tar xf test.tar.gz
make parcel


***Décrivez*** dans un fichier parcel.txt la complexité en temps et en espace de votre algorithme. 
Si vous trouvez comment faire, décrivez également comment on pourrait utiliser un espace constant sans augmenter la complexité en temps. 


***Implémentez*** dans un fichier parcel2.cc la fonction OptimalParcels() décrite dans le fichier parcel2.h:

```
#ifndef __PARCEL2_H
#define __PARCEL2_H

#include <vector>
using namespace std;

// Le problème est le même, mais au lieu de renvoyer le gain maximum, on
// veut renvoyer la liste des parcelles à cultiver pour obtenir le gain maximal.
//
// EXEMPLE:
// MaxGain([3, 7, 2, 1, 8, 4, 3]) = [1, 4, 6] (indices des parcelles choisies)
vector<int> OptimalParcels(const vector<int>& gain);

#endif  // __PARCEL2_H
```

Test: make parcel2 


# Exercice 2: Découpe optimale

Vous gérez une scierie qui coupe des planches. Pour simplifier, on supposera que toutes les planches font la même largeur: seule leur longueur diffère. 
Votre unique client, une grande enseigne de distribution, vous a donné une liste de modèles: chaque modèle à une longueur précise, et vous sera payé un prix donné. La demande est supposée infinie, pour tous les modèles. 
À chaque fois qu'un tronc d'arbre arrive, il sera automatiquement découpé en planches très longues d'une longueur L. 
Votre travail est de déterminer comment couper cette planche de longueur L en planches vendables, pour ***maximiser le prix total de vente.***

***Implémentez*** dans un fichier cut.cc la fonction ```OptimalCut()``` décrite dans le fichier cut.h:

```
#ifndef __CUT_H
#define __CUT_H

#include <vector>
using namespace std;

// Description d'un modèle de planche vendable: longueur et prix.
struct PricedCut {
  int length;  // Sera toujours >= 1.
  double price;  // Sera toujours > 0.
};

// Détermine la manière optimale de découper une planche de longueur L
// en planches vendables (pour maximiser le prix de vente total).
// Renvoie le prix de vente maximal.
// Écrit la liste des modèles choisis (un même modèle peut être répété
// plusieurs fois), dans un ordre quelquonque, dans le vecteur "cut_indices"
// (on écrira simplément l'indice des modèles).
//
// IMPORTANT: Le test de cette fonction est en 2 parties: d'abord, il teste
// simplement la valeur de renvoi, ensuite il teste "cut_indices". Si vous
// ne remplissez pas ce dernier, vous pourrez quand meme avoir des points.
//
// ATTENTION: les gains sont des nombres réels (double), pas des entiers.
//
// EXEMPLE:
// OptimalCut(257, {{40, 3.8}, {70, 6.7}, {90, 9.0}}) = 3.8 + 6.7 + 6.7 + 6.7
// avec cut_indices = [0, 1, 1, 1]. 
double OptimalCut(int L, const vector<PricedCut>& cuts,
                  vector<int>* cut_indices)

#endif  // __CUT_H
```

Test: make cut 
