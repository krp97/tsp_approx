#pragma once

#include <deque>
#include <functional>
#include <utility>

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "tabu_list.hpp"
#include "timer.hpp"

namespace tsp_approx {
class tabu_search
{
   public:
    tabu_search()  = delete;
    ~tabu_search() = default;

    tabu_search(const tabu_search&) = default;
    tabu_search(tabu_search&&)      = default;

    tabu_search& operator=(const tabu_search&) = default;
    tabu_search& operator=(tabu_search&&) = default;

    tabu_search(
        Adjacency_Matrix& matrix,
        std::function<Path(std::pair<size_t, size_t>, Path&, Adjacency_Matrix&)>
            neighbour_fnc);

    Path run(Timer<Path>* timer);

    // Neighbour functions
    static Path swap(std::pair<size_t, size_t> swap_index, Path& current_path,
                     Adjacency_Matrix& matrix);

   private:
    void main_loop(Path& current_path, Timer<Path>* timer);
    void examine_path(Path& current_path, unsigned idle_cycle);
    Path best_neighbour(Path& current_path, unsigned cycle);
    bool is_valid_tabu(const std::pair<size_t, size_t>& tabu_index,
                       const size_t iter_count);
    bool aspiration(Path& neighbour);
    void add_tabu(const std::pair<size_t, size_t>& tabu_index,
                  const size_t iterations);
    bool should_diversify();
    Path diversify(Path& current_path);
    void clear_tabu();

    Adjacency_Matrix& matrix_;
    std::vector<std::pair<size_t, size_t>> unique_pairs_;
    std::vector<std::vector<unsigned>> tabu_list_;
    std::function<Path(std::pair<size_t, size_t>, Path&, Adjacency_Matrix&)>
        neighbour_fnc_;

    Path best_path_;
    const unsigned tabu_cooldown    = 10;
    const unsigned idle_cycle_limit = 500;
};
}  // namespace tsp_approx
