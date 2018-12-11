#include <iostream>
#include "../include/adjacency_matrix.hpp"

int main()
{
    auto matrix{Adjacency_Matrix(
        "C:\\Users\\Desktop\\Desktop\\Github\\tsp_approx\\data\\ftv47.atsp")};

    std::fstream file;
    file.exceptions(std::fstream::failbit | std::fstream::badbit);

    file.open("C:\\Users\\Desktop\\Desktop\\Github\\tsp_approx\\data\\out.txt");

    file << matrix.to_string();
    file.close();
    return 0;
}