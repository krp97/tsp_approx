#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <math.h>

class Adjacency_Matrix{

friend class File_Handler;

public:

    Adjacency_Matrix();
    Adjacency_Matrix(std::vector<std::vector<int>> input);
    Adjacency_Matrix(const std::string& filename);
    Adjacency_Matrix(const size_t nodes);
	virtual ~Adjacency_Matrix() = default;

    bool operator==(const Adjacency_Matrix& rhs) const;
    bool operator!=(const Adjacency_Matrix& rhs) const;
    std::vector<int>& operator[](const int index);

    size_t size() const;
    std::string to_string() const;
    std::vector<std::vector<int>> data() const;

    virtual std::vector<int> get_neighbours(int node) const;

protected:

    std::vector<std::vector<int>> a_matrix_;

    int find_longest_number() const;
    void rows_to_string(std::string& output, int most_digits) const;
    void cols_to_string(std::string& output, const std::vector<int>& row, int most_digits) const;
    void pretty_string(std::string& str_matrix) const;
    int get_digits(const int number) const;

private:

    void fill_with_random();
    std::vector<int> get_random_row();
    bool load_from_file(std::fstream& file);
    void load_data(std::fstream& file);
    size_t parse_size_input(std::string& size);
    void resize_matrix(size_t size);
    std::vector<int> line_to_vec(std::string& line);
};