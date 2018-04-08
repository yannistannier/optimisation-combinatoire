#include "menu.h"
#include <string>
#include "ortools/linear_solver/linear_solver.h"

using namespace operations_research;

vector<double> MenuMoinsCher(
    const vector<double>& ajr,
    const vector<vector<double>>& apports_par_ingredient,
    const vector<double>& prix_par_ingredient) {
  MPSolver solver("Mon solveur", MPSolver::GLOP_LINEAR_PROGRAMMING);
  const int num_ingredients = apports_par_ingredient.size();
  const int num_elements = ajr.size();

  // CONSEILS -- BIEN LES LIRE EN ENTIER!
  // - Regarder le fichier "../examples/cpp/linear_programming.cc" pour voir
  //   comment définir des variables, des contraintes, et l'objectif.
  // - Contrairement a l'exemple, on a pas un nombre constant, prédéfini, de
  //   variables et de contraintes: elles dépendent de l'entrée. Il peut
  //   être utile de créér un tableau de MPVariable* stockant les variables
  //   créées pour modéliser le problème. Idem pour les contraintes.
  //   Et on les crééra dans des boucles "for" a priori.
  // - N'oubliez pas qu'après Solve() il faut encore renvoyer la solution
  //   dans le format demandé!

  const double infinity = solver.infinity();

  // L'objectif est de minimiser le prix.
  MPObjective* objective = solver.MutableObjective();
  objective->SetMinimization();

  // On definit les variables: q_ingredient[i] sera la quantité de
  // l'ingrédient #i.
  vector<MPVariable*> q_ingredient;
  for (int i = 0; i < num_ingredients; ++i) {
    MPVariable* var =
        solver.MakeNumVar(0, infinity, "Ingredient #" + std::to_string(i));
    q_ingredient.push_back(var);
    // Contribution de cet ingrédient au prix total (l'objectif).
    objective->SetCoefficient(var, prix_par_ingredient[i]);
  }

  // Pour chaque élément #e, on a la contrainte:
  // Somme_i(q_ingredient[i] * apport_par_ingredient[i][e] >= ajr[e])
  for (int e = 0; e < num_elements; ++e) {
    MPConstraint* ct = solver.MakeRowConstraint(ajr[e], infinity);
    for (int i = 0; i < num_ingredients; ++i) {
      ct->SetCoefficient(q_ingredient[i], apports_par_ingredient[i][e]);
    }
  }

  // On résout! Le problème devrait admettre une solution.
  solver.Solve();

  // On renvoie la solution.
  vector<double> quantites;
  for (MPVariable* q : q_ingredient) {
    quantites.push_back(q->solution_value());
  }
  return quantites;
}
