#include <iostream>
#include "../include/adjacency_matrix.hpp"
#include "../include/greedy_search.hpp"

int main()
{
    auto matrix{Adjacency_Matrix(
        "C:\\Users\\Desktop\\Desktop\\Github\\tsp_approx\\data\\tsp_6_2.txt")};

    auto gs = tsp_approx::greedy_search(matrix);
    std::cout << gs.run().to_string();
}