#include "../include/tabu_list.hpp"
namespace tsp_approx {

Tabu_List::Tabu_List(std::vector<std::vector<unsigned>> tabu)
    : tabu_list_ {tabu} {};

Tabu_List::Tabu_List(size_t size)
    : tabu_list_(size, std::vector<unsigned>(size, 0))
{
}

std::vector<unsigned>& Tabu_List::operator[](const size_t index)
{
    return tabu_list_[index];
}

bool Tabu_List::is_valid_tabu(const std::pair<size_t, size_t>& tabu_index,
                              const size_t iter_count)
{
    return tabu_list_[tabu_index.first][tabu_index.second] < iter_count;
}

void Tabu_List::add_tabu(const std::pair<size_t, size_t>& tabu_index,
                         const size_t iterations)
{
    tabu_list_[tabu_index.first][tabu_index.second] = iterations;
    tabu_list_[tabu_index.second][tabu_index.first] = iterations;
}

}  // namespace tsp_approx
