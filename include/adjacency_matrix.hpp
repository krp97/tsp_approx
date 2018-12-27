#pragma once

#include <math.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

class Adjacency_Matrix
{
    friend class File_Handler;

   public:
    Adjacency_Matrix() = default;
    Adjacency_Matrix(std::vector<std::vector<int>> input);
    Adjacency_Matrix(const std::string& filename);
    Adjacency_Matrix(const size_t nodes);
    ~Adjacency_Matrix() = default;

    bool operator==(const Adjacency_Matrix& rhs) const;
    bool operator!=(const Adjacency_Matrix& rhs) const;
    std::vector<int>& operator[](const int index);

    std::vector<std::vector<int>>::iterator begin();
    std::vector<std::vector<int>>::iterator end();
    std::vector<std::vector<int>>::reverse_iterator rbegin();
    std::vector<std::vector<int>>::reverse_iterator rend();

    size_t size() const;
    std::string to_string() const;
    std::vector<std::vector<int>> data() const;

    std::vector<int> get_neighbours(int node) const;

   private:
    std::vector<std::vector<int>> a_matrix_;

    void rows_to_string(std::string& output) const;
    void cols_to_string(std::string& output, const std::vector<int>& row) const;

    void fill_with_random();
    std::vector<int> get_row_with_random();

    bool load_from_file(std::fstream& file);
    void load_data(std::fstream& file);
    size_t parse_size_input(std::string& size);
    void resize_matrix(size_t size);
    std::vector<int> line_to_vec(std::string& line);
};