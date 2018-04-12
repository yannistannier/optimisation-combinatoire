#include "job0.h"
#include "ortools/linear_solver/linear_solver.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;
using namespace operations_research;

// Cette fonction nous aide a extraire la resource numero #n:
// 0->cpu, 1->ram, 2->disk.
double NthResource(const Resources& r, int n) {
  return n == 0 ? r.cpu : n == 1 ? r.ram : r.disk;
}

// Un copier-coller de la fonction de job.cc, mais avec une time_limit!
vector<int> BestJobAssignment(const vector<Resources>& jobs,
                              const vector<double>& profits,
                              const vector<Resources>& machines,
                              double time_limit_seconds) {
  MPSolver solver("Mon solveur", MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);
  const int num_jobs = jobs.size();
  const int num_machines = machines.size();

  MPObjective* objective = solver.MutableObjective();
  objective->SetMaximization();

  // On definit les variables: var[i][j]=1 si on fait tourner le job #i sur la
  // machine #j.
  vector<vector<MPVariable*>> var(num_jobs);
  for (int i = 0; i < num_jobs; ++i) {
    for (int j = 0; j < num_machines; ++j) {
      MPVariable* v = solver.MakeBoolVar("Job" + std::to_string(i) + "On" +
                                         std::to_string(j));
      var[i].push_back(v);
      objective->SetCoefficient(v, profits[i]);
    }
  }

  // Chaque job tourne au plus une fois.
  for (int i = 0; i < num_jobs; ++i) {
    MPConstraint* ct = solver.MakeRowConstraint(0, 1, "");  // TODO: name
    for (int j = 0; j < num_machines; ++j) {
      ct->SetCoefficient(var[i][j], 1.0);
    }
  }

  // Les jobs tournant sur une machine ne doivent pas consommer plus de
  // resources que la machine! On fait la meme chose pour chaque type de
  // resource.
  for (int j = 0; j < num_machines; ++j) {
    for (int res = 0; res < 3; ++res) {
      MPConstraint* ct =  // TODO: name
          solver.MakeRowConstraint(0, NthResource(machines[j], res), "");
      for (int i = 0; i < num_jobs; ++i) {
        ct->SetCoefficient(var[i][j], NthResource(jobs[i], res));
      }
    }
  }

  // On résout! Le problème devrait admettre une solution optimale
  // trouvable sans trop de problème.
  solver.set_time_limit(1000 * time_limit_seconds);
  const auto status = solver.Solve();
  vector<int> assignment(num_jobs, -1);
  if (status == MPSolver::OPTIMAL || status == MPSolver::FEASIBLE) {
    // On lit la solution.
    for (int i = 0; i < num_jobs; ++i) {
      for (int j = 0; j < num_machines; ++j) {
        if (var[i][j]->solution_value() > 0.5) {
          if (assignment[i] != -1) {
            cerr << "BUG: double assignment, Job #" << i << ", machines #"
                 << assignment[i] << " and #" << j << endl;
            exit(1);
          }
          assignment[i] = j;
        }
      }
    }
  }
  return assignment;
}

double Profit(const vector<double>& profits, const vector<int>& assignment) {
  double sum = 0;
  for (int i = 0; i < profits.size(); ++i) {
    if (assignment[i] >= 0) sum += profits[i];
  }
  return sum;
}

// On divise le probleme en "chunks". Voir le code.
vector<int> BestJobAssignmentSplit(const vector<Resources>& jobs,
                                   const vector<double>& profits,
                                   const vector<Resources>& machines,
                                   int num_chunks, int jobs_per_chunk) {
  const int num_jobs = jobs.size();
  const int num_machines = machines.size();
  vector<int> assignment(num_jobs, -1);
  const double time_per_chunk = 9.0 / num_chunks;
  // job_indices regroupera l'ensemble des jobs dans le chunk courant.
  vector<int> job_indices;
  int cur_job = 0;
  // On resout, chunk par chunk.
  int start_machine_index = 0;
  for (int i = 0; i < num_chunks; ++i) {
    // On ajoute les jobs dans la fenetre du chunk, un par un...
    while (cur_job < num_jobs && job_indices.size() < jobs_per_chunk) {
      job_indices.push_back(cur_job++);
    }
    // On determine la fenetre des machines...
    int end_machine_index = (int64(i + 1) * num_machines) / num_chunks;
    vector<int> machine_indices;
    for (int i = start_machine_index; i < end_machine_index; ++i) {
      machine_indices.push_back(i);
    }
    // On extrait le sous-probleme
    vector<Resources> subjobs;
    vector<double> subprofits;
    vector<Resources> submachines;
    for (int j : job_indices) {
      subjobs.push_back(jobs[j]);
      subprofits.push_back(profits[j]);
    }
    for (int m : machine_indices) {
      submachines.push_back(machines[m]);
    }
    // On le resout en un temps adapté.
    const vector<int> sub_assignment =
        BestJobAssignment(subjobs, subprofits, submachines, time_per_chunk);
    // On mappe la sous-solution sur la solution globale.
    for (int subj = 0; subj < subjobs.size(); ++subj) {
      const int subm = sub_assignment[subj];
      if (subm == -1) continue;
      assignment[job_indices[subj]] = machine_indices[subm];
    }
    // On enleve les jobs qui viennent d'etre assignés.
    job_indices.erase(
        std::remove_if(job_indices.begin(), job_indices.end(),
                       [&assignment](int j) { return assignment[j] >= 0; }),
        job_indices.end());
    // Et c'est fini! On fait suivre la fenetre des machines.
    start_machine_index = end_machine_index;
  }
  cerr << num_chunks << " chunks of: " << jobs_per_chunk << " jobs, "
       << num_machines / num_chunks << " machines, Time:" << time_per_chunk
       << "s, Profit: " << Profit(profits, assignment) << endl;
  return assignment;
}

vector<int> BestJobAssignment0(const vector<Resources>& jobs,
                               const vector<double>& profits,
                               const vector<Resources>& machines) {
  // Magic formulae, tuned by repeated experiments. See job0_experiments.cc
  const int num_chunks =
      jobs.size() < 100
          ? 1
          : jobs.size() < 150
                ? 3
                : jobs.size() < 300 ? 18 : int(machines.size() * 0.97);
  const int jobs_per_chunk =
      num_chunks == 1 ? jobs.size() : std::min(1250, int(jobs.size() * 0.97));
  return BestJobAssignmentSplit(jobs, profits, machines, num_chunks,
                                jobs_per_chunk);
}
