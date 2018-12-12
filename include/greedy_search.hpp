#pragma once
#include "adjacency_matrix.hpp"
#include "path.hpp"

namespace tsp_approx {

class greedy_search {
   public:
    greedy_search() = delete;

    greedy_search(greedy_search&) = default;
    ~greedy_search()              = default;

    greedy_search(Adjacency_Matrix& matrix);

    Path run();

   private:
    Adjacency_Matrix& matrix_;

    int add_node(std::vector<int>& row, std::vector<bool>& visited, Path& path);
};
}  // namespace tsp_approx