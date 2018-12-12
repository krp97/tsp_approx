#pragma once

#include <vector>
#include <string>

class Path{

public:

    std::vector<int> path_;
    int cost_;
	std::string algo_name_;

    Path();
    Path(std::vector<int> path, const int cost, const std::string& algo_name);
    ~Path() = default;

    void add_to_path(const int node, const int cost);
    
    int get_prev_city();

    std::string to_string();

private:

    void pretty_string(std::string& path, int line_len);
	std::string pretty_title(const std::string& title, const unsigned line_len) const;
    std::string get_path_str();
    std::string get_cost_str();
};