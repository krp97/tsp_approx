#include "../include/tsp.hpp"

tsp::tsp(double time_limit, double temp_start, double temp_factor)
    : time_limit_{time_limit},
      temp_start_{temp_start},
      temp_factor_{temp_factor}
{
}

Path tsp::simulated_annealing(
    std::function<double(double temperature, double temp_factor, int cycle)>
        cooling_fnc)
{
    auto data = tsp_approx::sim_annealing::annealing_data(
        temp_start_, temp_factor_, time_limit_);
    auto sa = tsp_approx::sim_annealing(data, matrix_, cooling_fnc);

    Timer<Path> timer = Timer<Path>(
        [&sa](Timer<Path>* timer) -> Path { return sa.run(timer); });
    timer.run();

    return timer.get_output();
}

Path tsp::tabu_search(
    std::function<Path(Adjacency_Matrix&, const Path&)> neighbour_fnc)
{
    auto ts = tsp_approx::tabu_search(time_limit_, matrix_, neighbour_fnc);
    Timer<Path> timer = Timer<Path>(
        [&ts](Timer<Path>* timer) -> Path { return ts.run(timer); });
    timer.run();

    return timer.get_output();
}

bool tsp::load_from_file(std::string filepath)
{
    try {
        matrix_   = Adjacency_Matrix(filepath);
        is_loaded = true;
    }
    catch (const std::invalid_argument&) {
        return false;
    }
    return true;
}