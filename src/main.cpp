#include <time.h>
#include <iostream>
#include <random>
#include "../include/adjacency_matrix.hpp"
#include "../include/file_converter.hpp"
#include "../include/greedy_search.hpp"
#include "../include/sim_annealing.hpp"

int main()
{
    srand(time(NULL));
    auto matrix =
        Adjacency_Matrix("/home/laptop/Desktop/git/tsp_approx/data/tsp_48.txt");
    auto data =
        tsp_approx::sim_annealing::annealing_data(11000, 0.99999, 30000);
    auto sa = tsp_approx::sim_annealing(data, matrix,
                                        tsp_approx::sim_annealing::swap);

    std::cout << sa.run().to_string();
    return 0;
}