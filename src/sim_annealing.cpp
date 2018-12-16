#include "../include/sim_annealing.hpp"
#include "../include/greedy_search.hpp"
#include "utils.cpp"

#include <math.h>
#include <iostream>
#include <random>

namespace tsp_approx {
int iterations{0};
sim_annealing::sim_annealing(
    const annealing_data& data, Adjacency_Matrix& matrix,
    std::function<Path(Path&, Adjacency_Matrix&)> neighbour_fnc)
    : sa_data{data}, matrix_{matrix}, neighbour_fnc_{neighbour_fnc}
{
}

Path sim_annealing::run()
{
    auto gs{greedy_search(matrix_)};
    Path current_path = gs.run();
    best_path         = current_path;
    annealing(current_path);
    return best_path;
}

void sim_annealing::annealing(Path& current_path)
{
    double temperature = sa_data.temperature_;
    start_time         = utils::time_now();
    //
    while (!check_time_bound(utils::time_now())) {
        Path new_path = neighbour_fnc_(current_path, matrix_);
        update_path(new_path, current_path, temperature);
        temperature *= sa_data.temp_factor_;
        iterations++;
    }
    std::cout << "\ntemp " << temperature << std::endl;
    std::cout << "iter:" << iterations << std::endl;
}

bool sim_annealing::check_time_bound(double current_time)
{
    return current_time - start_time >= sa_data.time_limit_;
}

void sim_annealing::update_path(Path& new_path, Path& current_path,
                                double temperature)
{
    if (new_path < current_path) {
        current_path = new_path;
        best_path    = current_path < best_path ? current_path : best_path;
    }
    else if (utils::random_double(0.0, 1.0) <
             calc_probability(new_path, current_path, temperature)) {
        current_path = new_path;
    }
}

double sim_annealing::calc_probability(Path& new_path, Path& current_path,
                                       double temperature)
{
    int cost_diff = (current_path.cost_ - new_path.cost_);
    return temperature <= 0 ? 0 : exp(cost_diff / temperature);
}

Path sim_annealing::swap(Path& current_path, Adjacency_Matrix& matrix)
{
    Path cpy_path = current_path;
    int index1    = utils::random_int(1, current_path.path_.size() - 2);
    int index2    = utils::random_int(1, current_path.path_.size() - 2);

    auto it1{std::begin(cpy_path) + index1};
    auto it2{std::begin(cpy_path) + index2};

    std::iter_swap(it1, it2);
    cpy_path.recalc_cost(matrix);
    return cpy_path;
}

Path sim_annealing::swap_n_reverse(Path& current_path, Adjacency_Matrix& matrix)
{
    /*Path cpy_path = current_path;
    int index1    = utils::random_int(1, current_path.path_.size() - 2);
    int index2    = utils::random_int(1, current_path.path_.size() - 2);

    auto it1{std::begin(cpy_path) + index1};
    auto it2{std::begin(cpy_path) + index2};*/
}

Path sim_annealing::insertion(Path& current_path, Adjacency_Matrix& matrix)
{
    /*Path cpy_path     = current_path;
    int index_to_move = utils::random_int(1, current_path.path_.size() - 2);
    int destination   = utils::random_int(1, current_path.path_.size() - 2);

    auto it{std::begin(cpy_path) + index_to_move};
    std::rotate(it, it + 1, it + destination);
    cpy_path.recalc_cost(matrix);
    return cpy_path;*/
}
}  // namespace tsp_approx
