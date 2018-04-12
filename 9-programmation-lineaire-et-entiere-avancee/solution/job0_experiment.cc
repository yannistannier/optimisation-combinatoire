#include "job0.h"
#include "ortools/linear_solver/linear_solver.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;
using namespace operations_research;

// Declarations des fonctions de job0.cc qui ne sont pas exposées dans job0.h

double Profit(const vector<double>& profits, const vector<int>& assignment);

vector<int> BestJobAssignmentSplit(const vector<Resources>& jobs,
                                   const vector<double>& profits,
                                   const vector<Resources>& machines,
                                   int num_chunks, int jobs_per_chunk);

// Ternary search: Quand on suppose qu'une fonction admet un unique maximum
// local, et qu'elle est donc croissante, puis decroissante, on peut chercher
// ce maximum, un peu comme une binary search en plus compliqué.
// Voir: https://en.wikipedia.org/wiki/Ternary_search (pas dispo en français!)

template <class T>
class TernarySearch {
 public:
  struct Point {
    int x;
    T out;
    double val;
  };

  static Point FindMax(std::function<double(int, T*)> F, int mini, int maxi);
};

template <class T>
typename TernarySearch<T>::Point TernarySearch<T>::FindMax(
    std::function<double(int, T*)> F, int mini, int maxi) {
  Point lo;
  lo.x = mini;
  auto eval = [&F](Point* p) { p->val = F(p->x, &p->out); };
  eval(&lo);
  if (mini == maxi) return lo;
  Point hi;
  hi.x = maxi;
  eval(&hi);
  Point mid = hi;
  // Gallop left..
  while (lo.x + 1 < hi.x) {
    mid.x = (lo.x + hi.x) / 2;
    eval(&mid);
    if (mid.val > lo.val) break;
    hi = mid;
  }
  if (mid.val <= lo.val) return lo;
  // Gallop right..
  while (mid.val < hi.val) {
    lo = mid;
    mid.x = (lo.x + hi.x) / 2;
    if (mid.x == lo.x) break;
    eval(&mid);
  }
  if (mid.val <= hi.val) return hi;
  // Ternary search proper.
  while (lo.x + 2 < hi.x) {
    Point mid1 = mid;
    Point mid2 = mid;
    if (hi.x - mid.x > mid.x - lo.x) {
      mid2.x = (mid.x + hi.x) / 2;
      eval(&mid2);
    } else {
      mid1.x = (lo.x + mid.x) / 2;
      eval(&mid1);
    }
    if (mid1.val < mid2.val) {
      lo = mid1;
      mid = mid2;
    } else {
      hi = mid2;
      mid = mid1;
    }
  }
  return mid;
}

// Cette fonction va rechercher les parametres optimaux
// (num_chunks, jobs_per_chunk) à donner à BestJobAssignmentSplit()
// pour resoudre le probleme donné.
// C'est très lent, car on se donne les 10 secondes reglementaires pour
// chaque couple de paramètres! Heureusement la double ternary search
// limite les degats, un peu.
vector<int> BestJobAssignmentMeta(const vector<Resources>& jobs,
                                  const vector<double>& profits,
                                  const vector<Resources>& machines) {
  typedef typename TernarySearch<vector<int>>::Point Point;
  std::function<Point(int)> FindBestJobSurchargeForFixedNumChunks =
      [&](int num_chunks) {
        const int min_jobs = (jobs.size() + num_chunks - 1) / num_chunks;
        const int max_jobs = jobs.size();
        return TernarySearch<vector<int>>::FindMax(
            [&](int jobs_per_chunk, vector<int>* assignment) -> double {
              *assignment = BestJobAssignmentSplit(jobs, profits, machines,
                                                   num_chunks, jobs_per_chunk);
              return Profit(profits, *assignment);
            },
            min_jobs, max_jobs);
      };
  double global_best = 0;
  int best_num_chunks = -1;
  int best_jobs_per_chunk = -1;
  Point best = TernarySearch<vector<int>>::FindMax(
      [&](int num_chunks, vector<int>* assignment) -> double {
        Point best = FindBestJobSurchargeForFixedNumChunks(num_chunks);
        if (best.val > global_best) {
          global_best = best.val;
          best_num_chunks = num_chunks;
          best_jobs_per_chunk = best.x;
        }
        *assignment = best.out;
        return best.val;
      },
      1, machines.size());
  cerr << "OPTIMAL: " << global_best << ", for " << best_num_chunks
       << " chunks, " << best_jobs_per_chunk << " jobs per chunk." << endl;
  return best.out;
}
