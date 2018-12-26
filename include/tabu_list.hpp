#pragma once
#include <vector>

namespace tsp_approx {
class Tabu_List {
   public:
    Tabu_List()  = delete;
    ~Tabu_List() = default;

    Tabu_List(const Tabu_List&) = default;
    Tabu_List(Tabu_List&&)      = default;

    Tabu_List& operator=(const Tabu_List&) = default;
    Tabu_List& operator=(Tabu_List&&) = default;

    Tabu_List(std::vector<std::vector<unsigned>> tabu);
    Tabu_List(size_t size);
    std::vector<unsigned>& operator[](const size_t index);

    bool is_valid_tabu(const std::pair<size_t, size_t>& tabu_index,
                       const size_t iter_count);
    void add_tabu(const std::pair<size_t, size_t>& tabu_index,
                  const size_t iterations);

   private:
    std::vector<std::vector<unsigned>> tabu_list_;
};
}  // namespace tsp_approx