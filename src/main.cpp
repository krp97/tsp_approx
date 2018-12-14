#include <iostream>
#include "../include/adjacency_matrix.hpp"
#include "../include/file_converter.hpp"
#include "../include/greedy_search.hpp"
#include "../include/sim_annealing.hpp"

int main()
{
    auto matrix = Adjacency_Matrix(
        "C:\\Users\\Desktop\\Desktop\\Github\\tsp_approx\\data\\tsp_48.txt");

    auto data =
        tsp_approx::sim_annealing::annealing_data(10000, 0.99999, 300000);
    auto sa = tsp_approx::sim_annealing(data, matrix);
    std::cout << sa.run().to_string();
    return 0;
}