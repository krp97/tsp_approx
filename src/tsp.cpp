#include "../include/tsp.hpp"

tsp::tsp(double time_limit, double temp_start, double temp_factor)
    : time_limit_ {time_limit}, temp_factor_ {temp_factor}
{
}

int tsp::get_matrix_size() const { return matrix_.size(); }

Path tsp::simulated_annealing(
    std::function<double(double temperature, double temp_factor, int cycle)>
        cooling_fnc)
{
    auto sa {tsp_approx::sim_annealing(temp_factor_, matrix_, cooling_fnc)};
    Timer<Path> timer =
        Timer<Path>([&sa](Timer<Path>* timer) -> Path { return sa.run(timer); },
                    time_limit_);
    timer.run();
    return timer.get_output();
}

Path tsp::tabu_search(
    std::function<Path(std::pair<size_t, size_t>, Path&, Adjacency_Matrix&)>
        neighbour_fnc)
{
    auto ts {tsp_approx::tabu_search(matrix_, neighbour_fnc)};
    Timer<Path> timer =
        Timer<Path>([&ts](Timer<Path>* timer) -> Path { return ts.run(timer); },
                    time_limit_);
    timer.run();
    return timer.get_output();
}

void tsp::load_from_file(std::string filepath)
{
    try
    {
        matrix_   = Adjacency_Matrix(filepath);
        is_loaded = true;
    } catch (const std::invalid_argument&)
    {
        throw;
    }
}