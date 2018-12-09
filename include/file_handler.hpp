#pragma once

#include "../include/adjacency_matrix.hpp"

#include <string>
#include <fstream>

class File_Handler{
    
public:

    File_Handler() = delete;

    File_Handler(std::string filepath, Adjacency_Matrix& matrix);
    
    File_Handler& operator=(const File_Handler& rhs) = default;
    ~File_Handler() = default;

    bool run();
    std::string what() const;

private:
    Adjacency_Matrix& matrix_;
    std::string filepath_;
    std::string error_;
};