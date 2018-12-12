#include <chrono>
#include <iostream>
#include <random>

#include "../include/adjacency_matrix.hpp"
#include "../include/path.hpp"

namespace utils {

inline double time_now()
{
    auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(
                  std::chrono::high_resolution_clock::now())
                  .time_since_epoch();
    return ms.count();
}

inline Path greedy_search(Adjacency_Matrix& matrix)
{
    auto path{Path()};
    path.add_to_path(0, 0);
    for (auto& row : matrix) {
        auto min_element = std::min_element(row.begin(), row.end());
        path.add_to_path(min_element - row.begin(), *min_element);
    }
    int last_index = path.get_prev_city();
    path.add_to_path(0, matrix[last_index][0]);
    return path;
}

inline double random_double(double a, double b)
{
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline int random_int(int a, int b)
{
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

}  // namespace utils