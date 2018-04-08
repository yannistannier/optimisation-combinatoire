#include "cut.h"

double OptimalCut(int L, const vector<PricedCut>& cuts,
                  vector<int>* cut_indices) {
  cut_indices->clear();
  // Formule:
  // OptimalCut(L) =          Max             (x.price + OptimalCut(L - x.length)
  //                 | pour tout PricedCut x |
  //                 | tel que x.length <= L |
  // ou = 0 si il n'existe aucun PricedCut x tq x.length <= L
  //
  // Version itérative: on calcule d'abord les plus petites longueurs.
  vector<double> best_price(L + 1, 0.0);
  vector<int> best_cut(L + 1, -1);
  for (int l = 1; l <= L; ++l) {
    double best = 0.0;
    for (int i = 0; i < cuts.size(); ++i) {
      if (cuts[i].length <= l) {
        double price = cuts[i].price + best_price[l - cuts[i].length];
        if (price > best) {
          best = price;
          best_cut[l] = i;
        }
      }
    }
    best_price[l] = best;
  }
  // On remplit le vecteur "cut_indices" en remontant le chemin optimal.
  int l = L;
  while (true) {
    const int cut = best_cut[l];
    if (cut < 0) break;
    cut_indices->push_back(cut);
    l -= cuts[cut].length;
  }
  // On renvoie le meilleur prix de revient pour L.
  return best_price[L];
}
