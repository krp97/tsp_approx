#pragma once
#include <functional>

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "timer.hpp"

namespace tsp_approx {

class sim_annealing {
   public:
    struct annealing_data {
        annealing_data() = default;
        annealing_data(const double temp_factor, double time_limit)
            : temp_factor_{temp_factor}, time_limit_{time_limit} {};

        annealing_data(const annealing_data&) = default;
        annealing_data& operator=(const annealing_data&) = default;

       public:
        double temp_factor_;
        double time_limit_;
    };

    sim_annealing()                     = default;
    sim_annealing(const sim_annealing&) = default;
    ~sim_annealing()                    = default;

    sim_annealing(
        const annealing_data&, Adjacency_Matrix&,
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
    void calc_start_temperature();
    int find_min_edge();
    int find_max_edge();

    void annealing(Path&, Timer<Path>* timer);
    bool check_time_bound(Timer<Path>* timer);
    Path swap(Path& current_path, Adjacency_Matrix& matrix);
    void update_path(Path& new_path, Path& current_path, double temperature);
    double calc_probability(Path& new_path, Path& current_path,
                            double temperature);

    const annealing_data& sa_data;
    double start_temperature;
    Adjacency_Matrix& matrix_;
    std::function<double(double temperature, double temp_factor, int cycle)>
        cooldown_fnc_;

    Path best_path;
    double start_time;
};
}  // namespace tsp_approx