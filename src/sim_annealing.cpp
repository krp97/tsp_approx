#include "../include/sim_annealing.hpp"
#include "../include/greedy_search.hpp"
#include "utils.cpp"

#include <math.h>
#include <iostream>
#include <random>

namespace tsp_approx {

double sim_annealing::start_temperature_ = 0;

sim_annealing::sim_annealing(
    const double temp_factor, Adjacency_Matrix& matrix,
    std::function<double(double temperature, double temp_factor, int cycle)>
        cooldown_fnc)
    : temp_factor_ {temp_factor}, matrix_ {matrix}, cooldown_fnc_ {cooldown_fnc}
{
    start_temperature_ = [&] {
        return abs(static_cast<double>(find_min_edge()) * matrix_.size() -
                   static_cast<double>(find_max_edge()) * matrix_.size());
    }();
}

Path sim_annealing::run(Timer<Path>* timer)
{
    auto gs {greedy_search(matrix_)};
    Path current_path = gs.run();
    best_path_        = current_path;
    annealing(current_path, timer);
    return best_path_;
}

void sim_annealing::annealing(Path& current_path, Timer<Path>* timer)
{
    double temperature {start_temperature_};
    std::cout << "start: " << start_temperature_ << std::endl;
    bool flag = false;
    for (int cycle {0}; timer->is_finished(); ++cycle)
    {
        for (int i {0}; i < 5; ++i)
        {
            Path new_path = swap(current_path, matrix_);
            update_path(new_path, current_path, temperature, timer);
        }
        temperature = cooldown_fnc_(temperature, temp_factor_, cycle);
    }
    std::cout << "\n\n Best found at: " << best_time << std::endl;
}

Path sim_annealing::swap(Path& current_path, Adjacency_Matrix& matrix)
{
    Path cpy_path = current_path;

    int index1 = utils::random_int(1, cpy_path.size() - 2);
    int index2 = utils::random_int(1, cpy_path.size() - 2);
    auto it1 {std::begin(cpy_path) + index1};
    auto it2 {std::begin(cpy_path) + index2};
    std::iter_swap(it1, it2);

    cpy_path.recalc_cost(matrix);
    return cpy_path;
}

void sim_annealing::update_path(Path& new_path, Path& current_path,
                                double temperature, Timer<Path>* timer)
{
    if (new_path < current_path)
    {
        current_path = new_path;
        if (best_path_ > current_path)
        {
            best_path_ = current_path;
            best_time  = timer->get_elapsed();
        }
        // best_path_ = current_path < best_path_ ? current_path : best_path_;
    }
    else if (utils::random_double(0.0, 1.0) <
             calc_probability(new_path, current_path, temperature))
    {
        current_path = new_path;
    }
}

double sim_annealing::calc_probability(Path& new_path, Path& current_path,
                                       double temperature)
{
    int cost_diff = (current_path.get_cost() - new_path.get_cost());
    return temperature <= 0 ? 0 : exp(cost_diff / temperature);
}

double sim_annealing::linear_cooling(double temperature, double temp_factor,
                                     int cycle)
{
    return temperature * temp_factor;
}

double sim_annealing::logarithmical_cooling(double temperature,
                                            double temp_factor, int cycle)
{
    return sim_annealing::start_temperature_ /
           (1 + temp_factor * log(1.0 + static_cast<double>(cycle)));
}

double sim_annealing::exponential_cooling(double temperature,
                                          double temp_factor, int cycle)
{
    return sim_annealing::start_temperature_ * pow(temp_factor, cycle);
}

int sim_annealing::find_min_edge()
{
    int min = std::numeric_limits<int>::max();
    for (auto& row : matrix_)
        for (auto& col : row)
            min = std::min(min, col);
    return min;
}

int sim_annealing::find_max_edge()
{
    int max = std::numeric_limits<int>::min();
    for (auto& row : matrix_)
        for (auto& col : row)
            max = std::max(max, col);
    return max;
}

}  // namespace tsp_approx
