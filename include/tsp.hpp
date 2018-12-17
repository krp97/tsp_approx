#pragma once

#include <string>

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "sim_annealing.hpp"
#include "tabu_search.hpp"

class tsp {
   public:
    double time_limit_;
    double temp_start_;
    double temp_factor_;

    tsp() = default;
    tsp(double time_limit, double temp_start, double temp_factor);
    tsp(const tsp&) = default;
    ~tsp()          = default;

    bool load_from_file(std::string);

    Path simulated_annealing(
        std::function<double(double temperature, double temp_factor,
                             int cycle)> =
            tsp_approx::sim_annealing::linear_cooling);

    Path tabu_search(std::function<Path(Adjacency_Matrix&, const Path&)> =
                         tsp_approx::tabu_search::swap);

   private:
    Adjacency_Matrix matrix_;
    bool is_loaded = false;
};