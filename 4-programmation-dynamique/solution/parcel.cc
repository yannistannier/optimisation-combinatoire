#include "parcel.h"

int MaxGain(const vector<int>& gain) {
  // L'approche itérative et en espace constant est la plus simple à implémenter:
  // La formule pour le gain max d'un champ de longueur N est:
  // MaxGain(N) = Max(MaxGain(N-1),   // On ne cultive pas la derniere parcelle 
  //                  Gain[N-1] + MaxGain(N-2))  // On cultive la derniere parcelle
  // Donc il suffit de les calculer dans l'ordre, en se rappelant uniquement des
  // 2 dernières valeurs, comme pour fibonacci.
  int gi_minus_1 = 0;  // avant-derniere
  int gi = 0;  // derniere
  for (int i = 0; i < gain.size(); ++i) {
    const int g = max(gi, gain[i] + gi_minus_1);
    gi_minus_1 = gi;
    gi = g;
  }
  return gi;
}
