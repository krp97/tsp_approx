#pragma once
#include "adjacency_matrix.hpp"
#include "path.hpp"

namespace tsp_approx {

class sim_annealing {
   public:
    struct annealing_data {
        annealing_data(const int temperature, const int temp_factor,
                       double time_limit)
            : temperature_{temperature},
              temp_factor_{temp_factor},
              time_limit_{time_limit} {};

       public:
        const int temperature_;
        const int temp_factor_;
        double time_limit_;
    };

    sim_annealing()               = default;
    sim_annealing(sim_annealing&) = default;
    ~sim_annealing()              = default;

    sim_annealing(const annealing_data&, Adjacency_Matrix&);

    Path run();

   private:
    void annealing(Path&);
    bool check_time_bound(double);

    Path neighbour(Path&);
    void update_path(Path& new_path, Path& current_path, int temperature);
    double calc_probability(Path& new_path, Path& current_path,
                            int temperature);

    const int temperature_limit_;
    const int temp_factor_;
    double time_limit_;
    Adjacency_Matrix& matrix_;

    Path best_path;
    double start_time;
    const int iterations = 5;
};
}  // namespace tsp_approx