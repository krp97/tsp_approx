#include "../include/tabu_search.hpp"
#include "../include/greedy_search.hpp"
#include "utils.cpp"

namespace tsp_approx {

tabu_search::tabu_search(
    Adjacency_Matrix& matrix,
    std::function<Path(std::pair<size_t, size_t>, Path&, Adjacency_Matrix&)>
        neighbour_fnc)
    : matrix_{matrix},
      tabu_list_(matrix_.size(), std::vector<unsigned>(matrix_.size(), 0)),
      neighbour_fnc_{neighbour_fnc}
{
}

Path tabu_search::run(Timer<Path>* timer)
{
    auto gs{greedy_search(matrix_)};
    Path current_path = gs.run();
    best_path_ = Path(std::vector<int>(), std::numeric_limits<int>::max(), "");
    return main_loop(current_path, timer);
}

Path tabu_search::main_loop(Path& current_path, Timer<Path>* timer)
{
    for (unsigned cycle{0}, idle_cycle{0}; timer->is_finished(); ++cycle) {
        current_path = best_neighbour(current_path, cycle);
        examine_path(current_path, idle_cycle);
    }
    return current_path;
}

Path tabu_search::best_neighbour(Path& current_path, unsigned cycle)
{
    Path best = Path(std::vector<int>(), std::numeric_limits<int>::max(), "");
    std::pair<int, int> best_permutation;
    auto permutations{get_all_index_pairs(current_path)};

    for (auto& perm : permutations) {
        Path temp_path = neighbour_fnc_(perm, current_path, matrix_);

        if (is_valid_tabu(perm, temp_path.cost_)) {
            best             = temp_path < best ? temp_path : best;
            best_permutation = perm;
        }
    }

    add_tabu(best_permutation, cycle + tabu_cooldown);
    return best;
}

std::vector<std::pair<size_t, size_t>> tabu_search::get_all_index_pairs(
    Path& path)
{
    auto all_permutations{std::vector<std::pair<size_t, size_t>>()};
    for (int i{1}; i < path.size() - 2; ++i)
        for (int j{i + 1}; j < path.size() - 2; ++j)
            all_permutations.push_back({i, j});
    return all_permutations;
}

void tabu_search::examine_path(Path& current_path, unsigned idle_cycle)
{
    if (current_path < best_path_) {
        best_path_ = current_path;
        idle_cycle = 0;
    }
    ++idle_cycle;
    if (idle_cycle >= idle_cycle_limit) {
        current_path = diversify(current_path);
        idle_cycle   = 0;
    }
}

Path tabu_search::diversify(Path& current_path)
{
    clear_tabu();
    Path new_path = current_path;
    std::random_shuffle(new_path.begin() + 1, new_path.end() - 2);
    new_path.recalc_cost(matrix_);
    return new_path;
}

void tabu_search::add_nodes(std::vector<int>& nodes, Path& path_to_add)
{
    for (auto& node : nodes) path_to_add.add_to_path(node, 0);
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
    tabu_list_[tabu_index.first][tabu_index.second] = iterations;
    tabu_list_[tabu_index.second][tabu_index.first] = iterations;
}

void tabu_search::clear_tabu()
{
    std::for_each(tabu_list_.begin(), tabu_list_.end(),
                  [](std::vector<unsigned> row) {
                      std::fill(row.begin(), row.end(), 0);
                  });
}

static Path swap(std::pair<size_t, size_t> swap_index, Path& current_path,
                 Adjacency_Matrix& matrix)
{
    Path temp_path = current_path;
    std::swap(temp_path[swap_index.first], temp_path[swap_index.second]);
    temp_path.recalc_cost(matrix);
    return temp_path;
}
}  // namespace tsp_approx
