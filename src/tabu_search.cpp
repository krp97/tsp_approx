#include "../include/tabu_search.hpp"
#include "utils.cpp"

namespace tsp_approx {

tabu_search::tabu_search(
    double time_limit, const Adjacency_Matrix& matrix,
    std::function<Path(Adjacency_Matrix&, const Path&)> neighbour_fnc)
    : time_limit_{time_limit}, matrix_{matrix}, neighbour_fnc_{neighbour_fnc}
{
}

Path tabu_search::run(Timer<Path>* timer) {}

bool tabu_search::check_time_bound(Timer<Path>* timer)
{
    return timer->get_elapsed() < time_limit_;
}

Path tabu_search::swap(Adjacency_Matrix& matrix, const Path& current_path)
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

Path tabu_search::swap_n_reverse(Adjacency_Matrix& matrix,
                                 const Path& current_path)
{
    /*Path cpy_path = current_path;
    int index1    = utils::random_int(1, current_path.path_.size() - 2);
    int index2    = utils::random_int(1, current_path.path_.size() - 2);
    auto it1{std::begin(cpy_path) + index1};
    auto it2{std::begin(cpy_path) + index2};*/
}

Path tabu_search::insertion(Adjacency_Matrix& matrix, const Path& current_path)
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