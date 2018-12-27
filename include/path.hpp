#pragma once
#include <functional>
#include <string>
#include <vector>
#include "adjacency_matrix.hpp"

class Path
{
   public:
    std::vector<int> path_;
    int cost_;
    std::string algo_name_;

    Path();
    Path(std::vector<int> path, const int cost, const std::string& algo_name);
    const Path& operator=(const Path& rhs);
    ~Path()             = default;
    int& operator[](int index) { return path_[index]; };
    bool operator<(const Path& rhs) { return this->cost_ < rhs.cost_; };
    bool operator>(const Path& rhs) { return !(*this < rhs); };
    bool operator==(const Path& rhs) { return path_ == rhs.path_; };
    bool operator!=(const Path& rhs) { return !(*this == rhs); }

    std::vector<int>::iterator begin() { return path_.begin(); };
    std::vector<int>::iterator end() { return path_.end(); };

    int size() { return path_.size(); };

    void recalc_cost(Adjacency_Matrix& matrix);

    void add_to_path(const int node, const int cost);
    int get_prev_city();
    std::string to_string();

   private:
    void pretty_string(std::string& path, int line_len);
    std::string pretty_title(const std::string& title,
                             const unsigned line_len) const;
    std::string get_path_str();
    std::string get_cost_str();
};