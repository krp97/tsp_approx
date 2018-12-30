#pragma once
#include <functional>

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "timer.hpp"

namespace tsp_approx {

class sim_annealing
{
   public:
    sim_annealing()  = default;
    ~sim_annealing() = default;

    sim_annealing(const sim_annealing&) = default;
    sim_annealing(sim_annealing&&)      = default;

    sim_annealing& operator=(sim_annealing&&) = default;
    sim_annealing& operator=(const sim_annealing&) = default;

    sim_annealing(
        const double temp_factor, Adjacency_Matrix&,
        std::function<double(double temperature, double temp_factor, int cycle)>
            cooldown_fnc);

    Path run(Timer<Path>* timer);

    // Cooling functions
    static double linear_cooling(double temperature, double temp_factor,
                                 int cycle);
    static double logarithmical_cooling(double temperature, double temp_factor,
                                        int cycle);
    static double exponential_cooling(double temperature, double temp_factor,
                                      int cycle);

   private:
    int find_min_edge();
    int find_max_edge();

    void annealing(Path&, Timer<Path>* timer);
    Path swap(Path& current_path, Adjacency_Matrix& matrix);
    void update_path(Path& new_path, Path& current_path, double temperature,
                     Timer<Path>* timer);
    double calc_probability(Path& new_path, Path& current_path,
                            double temperature);

    static double start_temperature_;
    const double temp_factor_;
    double best_time = 0.0;
    std::function<double(double temperature, double temp_factor, int cycle)>
        cooldown_fnc_;

    Adjacency_Matrix& matrix_;
    Path best_path_;
};
}  // namespace tsp_approx