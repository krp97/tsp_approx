#include "../include/greedy_search.hpp"
#include <iostream>
namespace tsp_approx {
greedy_search::greedy_search(Adjacency_Matrix& matrix) : matrix_{matrix} {}

Path greedy_search::run()
{
    Path path;
    auto visited = std::vector<bool>(matrix_.size(), false);
    path.add_to_path(0, 0);
    visited[0] = true;

    int index{0};
    for (size_t i{0}; i < matrix_.size() - 1; ++i) {
        index = add_node(matrix_[index], visited, path);
    }

    path.add_to_path(0, matrix_[path.get_prev_city()][0]);
    return path;
}
int greedy_search::add_node(std::vector<int>& row, std::vector<bool>& visited,
                            Path& path)
{
    std::vector<int> vec_copy = row;
    bool exit                 = false;
    int index                 = 0;

    while (!exit) {
        auto min_element = std::min_element(vec_copy.begin(), vec_copy.end());
        index = std::find(row.begin(), row.end(), *min_element) - row.begin();

        if (!visited[index]) {
            path.add_to_path(index, matrix_[path.get_prev_city()][index]);
            exit           = true;
            visited[index] = true;
        }
        else
            vec_copy.erase(min_element);
    }
    return index;
}
}  // namespace tsp_approx
