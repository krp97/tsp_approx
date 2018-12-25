#include "../include/tabu_search.hpp"
#include "../include/greedy_search.hpp"
#include "utils.cpp"

namespace tsp_approx {

tabu_search::tabu_search(double time_limit, Adjacency_Matrix& matrix)
    : time_limit_{time_limit}, matrix_{matrix}
{
}

Path tabu_search::run(Timer<Path>* timer)
{
    auto gs{greedy_search(matrix_)};
    Path current_path = gs.run();
    best_path = Path(std::vector<int>(), std::numeric_limits<int>::max(), "");
    return ts(current_path, timer);
}

Path tabu_search::ts(Path current_path, Timer<Path>* timer)
{
    bool score1 = false;
    bool score2 = false;
    bool score3 = false;

    for (double div_start{utils::time_now()}; check_time_bound(timer);) {
        current_path = best_neighbour(current_path);

        if (current_path < best_path) {
            best_path = current_path;
            div_start = utils::time_now();
        }

        if (utils::time_now() - div_start >
            static_cast<double>(0.1 * 1000 * matrix_.size())) {
            current_path = diversify(current_path);
            div_start    = utils::time_now();
        }

        if (tabu_list.size() > matrix_.size())
            tabu_list.pop_front();
        if (timer->get_elapsed() > 30000 && !score1) {
            score1 = true;
            std::cout << best_path.to_string() << std::endl;
        }
        if (timer->get_elapsed() > 60000 && !score2) {
            score2 = true;
            std::cout << best_path.to_string() << std::endl;
        }
        if (timer->get_elapsed() > 90000 && !score3) {
            score3 = true;
            std::cout << best_path.to_string() << std::endl;
        }
    }
    return current_path;
}

Path tabu_search::best_neighbour(Path& current_path)
{
    Path temp_path;
    Path best = Path(std::vector<int>(), std::numeric_limits<int>::max(), "");
    std::pair<int, int> index_of_swap;

    for (int i{1}; i < current_path.size() - 1; ++i) {
        for (int j{i}; j < current_path.size() - 1; ++j) {
            temp_path = current_path;
            std::swap(temp_path[i], temp_path[j]);
            temp_path.recalc_cost(matrix_);

            if (is_valid_tabu({i, j}, temp_path.cost_)) {
                best          = temp_path < best ? temp_path : best;
                index_of_swap = {i, j};
            }
        }
    }

    tabu_list.push_back(index_of_swap);
    return best;
}

bool tabu_search::is_valid_tabu(std::pair<int, int> swap, int cost)
{
    auto exists = std::find(tabu_list.begin(), tabu_list.end(), swap);
    if (exists != std::end(tabu_list))
        return cost < best_path.cost_;  // Aspiration

    return true;
}

Path tabu_search::diversify(Path& current_path)
{
    tabu_list.clear();
    std::vector<int> nodes;
    Path new_path;

    for (int div = div_counter; div > 0; --div) {
        nodes = get_each_n(div, current_path);
        remove_duplicates(nodes, new_path);
        add_nodes(nodes, new_path);
    }

    div_counter++;
    new_path.recalc_cost(matrix_);
    return new_path;
}

void tabu_search::remove_duplicates(std::vector<int>& nodes, Path& new_path)
{
    auto to_remove =
        std::remove_if(nodes.begin(), nodes.end(), [&new_path](int node) {
            return std::find(new_path.begin(), new_path.end(), node) !=
                   std::end(new_path);
        });
    nodes.erase(to_remove, nodes.end());
}

std::vector<int> tabu_search::get_each_n(int n, Path& path)
{
    std::vector<int> output;
    for (int i{1}; i < path.size() - 1; i += n) {
        output.push_back(path[i]);
    }
    return output;
}

void tabu_search::add_nodes(std::vector<int>& nodes, Path& path_to_add)
{
    for (auto& node : nodes)
        path_to_add.add_to_path(node, 0);
}

bool tabu_search::check_time_bound(Timer<Path>* timer)
{
    return timer->get_elapsed() < time_limit_;
}
}  // namespace tsp_approx
