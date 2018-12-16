#pragma once
#include <functional>

#include "adjacency_matrix.hpp"
#include "path.hpp"

namespace tsp_approx {

class sim_annealing {
   public:
    struct annealing_data {
        annealing_data(const int temperature, const double temp_factor,
                       double time_limit)
            : temperature_{temperature},
              temp_factor_{temp_factor},
              time_limit_{time_limit} {};

       public:
        const int temperature_;
        const double temp_factor_;
        double time_limit_;
    };

    sim_annealing()                     = default;
    sim_annealing(const sim_annealing&) = default;
    ~sim_annealing()                    = default;

    sim_annealing(const annealing_data&, Adjacency_Matrix&,
                  std::function<Path(Path&, Adjacency_Matrix&)> neighbour_fnc);

    Path run();

    // Neighbour functions
    static Path swap(Path& current_path, Adjacency_Matrix&);
    static Path swap_n_reverse(Path& current_path, Adjacency_Matrix&);
    static Path insertion(Path& current_path, Adjacency_Matrix&);

   private:
    void annealing(Path&);
    bool check_time_bound(double);

    void update_path(Path& new_path, Path& current_path, double temperature);
    double calc_probability(Path& new_path, Path& current_path,
                            double temperature);

    const annealing_data& sa_data;
    Adjacency_Matrix& matrix_;
    std::function<Path(Path&, Adjacency_Matrix&)> neighbour_fnc_;

    Path best_path;
    double start_time;
};
}  // namespace tsp_approx