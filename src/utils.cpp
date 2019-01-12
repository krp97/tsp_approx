#include <chrono>
#include <iostream>
#include <random>

#include "../include/adjacency_matrix.hpp"
#include "../include/path.hpp"

namespace utils {

inline double random_double(double a, double b)
{
    std::default_random_engine generator(
        std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(a, b);
    double x = distribution(generator);
    return x;
}

inline int random_int(int a, int b)
{
    std::default_random_engine generator(
        std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

inline int factorial(unsigned a) { return a == 1 ? 1 : a * factorial(a - 1); }
}  // namespace utils