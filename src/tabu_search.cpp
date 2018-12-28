#include "../include/tabu_search.hpp"
#include "../include/greedy_search.hpp"
#include "utils.cpp"

namespace tsp_approx {

tabu_search::tabu_search(
    Adjacency_Matrix& matrix,
    std::function<Path(std::pair<size_t, size_t>, Path&, Adjacency_Matrix&)>
        neighbour_fnc)
    : matrix_ {matrix},
      tabu_list_(matrix_.size(), std::vector<unsigned>(matrix_.size(), 0)),
      neighbour_fnc_ {neighbour_fnc}
{
    // All possible unique pairs of indexes within the path.
    [&] {
        for (size_t i {1}; i <= matrix_.size() - 2; ++i)
            for (size_t j {i + 1}; j <= matrix_.size() - 1; ++j)
                unique_pairs_.push_back({i, j});
    }();
}

Path tabu_search::run(Timer<Path>* timer)
{
    auto gs {greedy_search(matrix_)};
    Path current_path {gs.run()};
    best_path_ = Path(std::vector<int>(), std::numeric_limits<int>::max(), "");
    main_loop(current_path, timer);
    return best_path_;
}

void tabu_search::main_loop(Path& current_path, Timer<Path>* timer)
{
    for (unsigned cycle {1}, idle_cycle {0}; timer->is_finished(); ++cycle)
    {
        current_path = best_neighbour(current_path, cycle);
        examine_path(current_path, idle_cycle);
    }
}

Path tabu_search::best_neighbour(Path& current_path, unsigned cycle)
{
    Path best = Path(std::vector<int>(), std::numeric_limits<int>::max(), "");
    auto best_pair = std::pair<size_t, size_t> {0, 0};

    for (auto& p : unique_pairs_)
    {
        if (is_valid_tabu(p, cycle))
        {
            Path temp_path = neighbour_fnc_(p, current_path, matrix_);
            if (temp_path < best)
            {
                best      = temp_path < best ? temp_path : best;
                best_pair = p;
            }
        }
    }

    add_tabu(best_pair, cycle + tabu_cooldown);
    return best.get_cost() != std::numeric_limits<int>::max() ? best
                                                              : current_path;
}

void tabu_search::examine_path(Path& current_path, unsigned& idle_cycle)
{
    if (current_path < best_path_)
    {
        best_path_ = current_path;
        idle_cycle = 0;
    }
    else if (idle_cycle >= idle_cycle_limit)
    {
        current_path = diversify(current_path);
        idle_cycle   = 0;
    }
    else
        ++idle_cycle;
}

Path tabu_search::diversify(Path& current_path)
{
    clear_tabu();
    Path new_path = current_path;
    std::random_shuffle(new_path.begin() + 1, new_path.end() - 2);
    new_path.recalc_cost(matrix_);
    return new_path;
}

bool tabu_search::is_valid_tabu(const std::pair<size_t, size_t>& tabu_index,
                                const size_t iter_count)
{
    return tabu_list_[tabu_index.first][tabu_index.second] < iter_count;
}

bool tabu_search::aspiration(Path& neighbour) { return neighbour < best_path_; }

void tabu_search::add_tabu(const std::pair<size_t, size_t>& tabu_index,
                           const size_t iterations)
{
    if (tabu_index != std::pair<size_t, size_t> {0, 0})
    {
        tabu_list_[tabu_index.first - 1][tabu_index.second - 1] = iterations;
        tabu_list_[tabu_index.second - 1][tabu_index.first - 1] = iterations;
    }
}

void tabu_search::clear_tabu()
{
    std::for_each(tabu_list_.begin(), tabu_list_.end(),
                  [](std::vector<unsigned> row) {
                      std::fill(row.begin(), row.end(), 0);
                  });
}

Path tabu_search::swap(std::pair<size_t, size_t> swap_index, Path& current_path,
                       Adjacency_Matrix& matrix)
{
    Path temp_path = current_path;
    std::swap(temp_path[swap_index.first], temp_path[swap_index.second]);
    temp_path.recalc_cost(matrix);
    return temp_path;
}

Path tabu_search::swap_n_reverse(std::pair<size_t, size_t> swap_index,
                                 Path& current_path, Adjacency_Matrix& matrix)
{
    Path temp_path {current_path};
    auto max_it {temp_path.begin() +
                 std::max(swap_index.first, swap_index.second)};
    auto min_it {temp_path.begin() +
                 std::min(swap_index.first, swap_index.second)};

    for (; max_it - min_it > 0; --max_it, ++min_it)
        std::iter_swap(max_it, min_it);

    temp_path.recalc_cost(matrix);
    return temp_path;
}

Path tabu_search::insertion(std::pair<size_t, size_t> swap_index,
                            Path& current_path, Adjacency_Matrix& matrix)
{
    Path temp_path {current_path};
    int value {temp_path[swap_index.first]};
    temp_path.erase(swap_index.first);
    temp_path.insert(swap_index.second, value);
    return temp_path;
}
}  // namespace tsp_approx
