#pragma once

#include <functional>

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "timer.hpp"

namespace tsp_approx {
class tabu_search {
   public:
    tabu_search() = delete;
    tabu_search(double time_limit, const Adjacency_Matrix& matrix,
                std::function<Path(Adjacency_Matrix&, const Path&)>);

    tabu_search(const tabu_search&) = default;
    ~tabu_search()                  = default;

    Path run(Timer<Path>* timer);

    // Neighbour functions
    static Path swap(Adjacency_Matrix& matrix, const Path& current_path);
    static Path swap_n_reverse(Adjacency_Matrix& matrix,
                               const Path& current_path);
    static Path insertion(Adjacency_Matrix& matrix, const Path& current_path);

   private:
    bool check_time_bound(Timer<Path>* timer);

    const Adjacency_Matrix& matrix_;
    const double time_limit_;
    std::function<Path(Adjacency_Matrix&, const Path&)> neighbour_fnc_;
};
}  // namespace tsp_approx
