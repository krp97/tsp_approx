#pragma once
#include "adjacency_matrix.hpp"
#include "path.hpp"

namespace tsp_approx {

class greedy_search {
   public:
    greedy_search() = delete;

    greedy_search(const greedy_search&) = default;
    ~greedy_search()                    = default;

    greedy_search(Adjacency_Matrix& matrix);

    Path run();

   private:
    Adjacency_Matrix& matrix_;
    void run(Path&, std::vector<bool>& visited);
    int get_minimum(std::vector<int>& row, std::vector<bool>& visited);
    bool all_visited(std::vector<bool>& visited);
};
}  // namespace tsp_approx