#include "../include/adjacency_matrix.hpp"
#include "../include/file_handler.hpp"

#include <math.h>
#include <iostream>
#include <sstream>

Adjacency_Matrix::Adjacency_Matrix(const std::string& filename)
    : a_matrix_{std::vector<std::vector<int>>()}
{
    File_Handler f(filename, *this);
    if (!f.run())
        throw std::invalid_argument(f.what());
}

Adjacency_Matrix::Adjacency_Matrix(const size_t nodes)
    : a_matrix_{std::vector<std::vector<int>>(nodes, std::vector<int>(nodes))}
{
    fill_with_random();
}

bool Adjacency_Matrix::operator==(const Adjacency_Matrix& rhs) const
{
    if (a_matrix_ == rhs.a_matrix_)
        return true;
    return false;
}

bool Adjacency_Matrix::operator!=(const Adjacency_Matrix& rhs) const
{
    return !(*this == rhs);
}

std::vector<int>& Adjacency_Matrix::operator[](const int index)
{
    return a_matrix_.at(index);
}

std::vector<std::vector<int>>::iterator Adjacency_Matrix::begin()
{
    return a_matrix_.begin();
}

std::vector<std::vector<int>>::iterator Adjacency_Matrix::end()
{
    return std::end(a_matrix_);
}

std::vector<std::vector<int>>::reverse_iterator Adjacency_Matrix::rbegin()
{
    return std::rend(a_matrix_);
}

std::vector<std::vector<int>>::reverse_iterator Adjacency_Matrix::rend()
{
    return std::rbegin(a_matrix_);
}

size_t Adjacency_Matrix::size() const { return a_matrix_.size(); }

std::string Adjacency_Matrix::to_string() const
{
    auto output{std::string()};
    rows_to_string(output);
    return output;
}

void Adjacency_Matrix::rows_to_string(std::string& output) const
{
    for (auto& rows : a_matrix_) {
        cols_to_string(output, rows);
        output += "\n";
    }
}

void Adjacency_Matrix::cols_to_string(std::string& output,
                                      const std::vector<int>& row) const
{
    for (auto& cols : row)
        output += std::to_string(cols) + " ";
}

std::vector<std::vector<int>> Adjacency_Matrix::data() const
{
    return a_matrix_;
}

void Adjacency_Matrix::fill_with_random()
{
    std::generate(a_matrix_.begin(), a_matrix_.end(),
                  [this]() { return get_row_with_random(); });
}

std::vector<int> Adjacency_Matrix::get_row_with_random()
{
    auto output{std::vector<int>(a_matrix_.size())};
    std::transform(output.begin(), output.end(), output.begin(),
                   [](int node) { return rand() % 100; });
    return output;
}

bool Adjacency_Matrix::load_from_file(std::fstream& in_file)
{
    try {
        load_data(in_file);
    }
    catch (const std::ifstream::failure&) {
        if (!in_file.eof())
            throw;
    }
    return true;
}

void Adjacency_Matrix::load_data(std::fstream& file)
{
    std::string line;
    std::getline(file, line);
    size_t size{parse_size_input(line)};
    resize_matrix(size);
    for (auto& rows : a_matrix_)
        load_row(file, rows);
}

size_t Adjacency_Matrix::parse_size_input(std::string& size_input)
{
    size_t size;
    auto iss{std::istringstream(size_input)};
    iss >> size;
    return iss.fail() ? 0 : size;
}

void Adjacency_Matrix::resize_matrix(size_t size)
{
    a_matrix_.resize(size, std::vector<int>(size));
}

// Reads as many lines as necessary to fill a row.
void Adjacency_Matrix::load_row(std::fstream& file, std::vector<int>& row)
{
    std::string line;
    int element_counter{0};
    while (element_counter < row.size()) {
        std::getline(file, line);
        std::stringstream iss(line);
        int number;
        for (; iss >> number; ++element_counter)
            row[element_counter] = number;
    }
}

std::vector<int> Adjacency_Matrix::get_neighbours(int node) const
{
    auto output{std::vector<int>()};
    for (size_t i{0}; i < a_matrix_[node].size(); ++i) {
        if (a_matrix_[node][i] != 0)
            output.push_back(i);
    }
    return output;
}