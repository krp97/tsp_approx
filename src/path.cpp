#include "../include/path.hpp"
#include <iostream>

Path::Path() : path_ {std::vector<int>()}, cost_ {0} {}

Path::Path(std::vector<int> path, const int cost, const std::string& algo_name)
    : path_ {path}, cost_ {cost}, algo_name_ {algo_name}
{
}

const Path& Path::operator=(const Path& rhs)
{
    path_ = rhs.path_;
    cost_ = rhs.cost_;
    return *this;
}

void Path::recalc_cost(Adjacency_Matrix& matrix)
{
    cost_ = 0;
    for (size_t i {0}; i < path_.size() - 1; ++i)
        cost_ += matrix[path_[i]][path_[i + 1]];
}

void Path::add_to_path(const int node, const int cost)
{
    path_.push_back(node);
    cost_ += cost;
}

void Path::erase(size_t index) { path_.erase(std::begin(path_) + index); }

void Path::insert(size_t index, int value)
{
    path_.insert(std::begin(path_) + index, value);
}

int Path::get_prev_city() { return path_[path_.size() - 1]; }

std::string Path::to_string()
{
    std::string path {get_path_str()};
    std::string cost {get_cost_str()};
    std::string output {path + "\n\n" + cost};
    return output;
}

std::string Path::get_path_str()
{
    auto output {std::string("Path >> ")};
    for (size_t i {0}; i < path_.size(); ++i)
    {
        output += std::to_string(path_[i]);
        if (i < path_.size() - 1)
            output += "->";
    }
    return output;
}

std::string Path::get_cost_str()
{
    return std::string("Cost >> " + std::to_string(cost_));
}
