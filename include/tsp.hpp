#pragma once

#include <string>

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "sim_annealing.hpp"

class tsp {
   public:
    double time_limit_;
    double temp_factor_;

    tsp()  = default;
    ~tsp() = default;

    tsp(const tsp&) = default;
    tsp(tsp&&)      = default;

    tsp& operator=(const tsp&) = default;
    tsp& operator=(tsp&&) = default;

    tsp(double time_limit, double temp_start, double temp_factor);

    void load_from_file(std::string);

    Path simulated_annealing(
        std::function<double(double temperature, double temp_factor,
                             int cycle)> =
            tsp_approx::sim_annealing::linear_cooling);

    bool is_loaded = false;

   private:
    Adjacency_Matrix matrix_;
};