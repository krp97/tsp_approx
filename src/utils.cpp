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

inline double random_double(double a, double b)
{
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double x = distribution(generator);
    return x;
}

inline int random_int(int a, int b)
{
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

inline int random_gauss_int(int mean, int deviation)
{
    std::random_device r;
    std::default_random_engine generator(r());
    std::normal_distribution<> distribution(mean, deviation);
    return std::round(distribution(generator));
}

}  // namespace utils