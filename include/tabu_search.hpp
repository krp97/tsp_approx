#pragma once

#include <deque>
#include <functional>
#include <utility>

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "timer.hpp"

namespace tsp_approx {
class tabu_search {
   public:
    tabu_search() = delete;
    tabu_search(double time_limit, Adjacency_Matrix& matrix);

    tabu_search(const tabu_search&) = default;
    ~tabu_search()                  = default;

    Path run(Timer<Path>* timer);

   private:
    Path ts(Path current_path, Timer<Path>* timer);
    Path best_neighbour(Path&);
    bool is_valid_tabu(std::pair<int, int> swap, int cost);
    bool check_time_bound(Timer<Path>* timer);
    Path diversify(Path& current_path);
    std::vector<int> get_each_n(int n, Path& path);
    void remove_duplicates(std::vector<int>& nodes, Path& new_path);
    void add_nodes(std::vector<int>& nodes, Path& path_to_add);

    Adjacency_Matrix& matrix_;
    std::deque<std::pair<int, int>> tabu_list;
    const double time_limit_;
    Path best_path;
    int div_counter = 2;
};
}  // namespace tsp_approx
