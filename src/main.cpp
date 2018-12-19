#include <time.h>
#include <iostream>
#include <random>
#include "../include/adjacency_matrix.hpp"
#include "../include/file_converter.hpp"
#include "../include/greedy_search.hpp"
#include "../include/menu_handler.hpp"
#include "../include/sim_annealing.hpp"
#include "../include/tabu_search.hpp"
#include "../include/timer.hpp"

int main()
{
    Menu m{Menu()};
    std::string subtitles[] = {
        "Ustaw czas wykonywania.", "Ustaw wspolczynnik chlodzenia.",
        "Wczytaj z pliku.", "Uruchom algorytmy.", "Wyjscie"};
    m.run(subtitles, 5, "Menu");
    return 0;
}