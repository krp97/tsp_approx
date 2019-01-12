#include <time.h>
#include <iostream>
#include <random>
#include "../include/adjacency_matrix.hpp"
#include "../include/file_converter.hpp"
#include "../include/greedy_search.hpp"
#include "../include/menu_handler.hpp"
#include "../include/sim_annealing.hpp"
#include "../include/timer.hpp"

int main()
{
    Menu m {Menu()};
    std::vector<std::string> subtitles = {
        "Set the time limit.",
        "Set the cooling factor.",
        "Load the graph from a file (.txt only).",
        "Run the algorithms.",
        "Convert from TSPLIB to txt.",
        "Exit"};
    m.run(subtitles, "Menu");
    return 0;
}