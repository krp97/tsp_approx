#include "../include/adjacency_matrix.hpp"
#include "../include/file_handler.hpp"

#include <iostream>
#include <math.h>
#include <sstream>

Adjacency_Matrix::Adjacency_Matrix()
{}

Adjacency_Matrix::Adjacency_Matrix(std::vector<std::vector<int>> matrix)
    : a_matrix_{ matrix }
{}

Adjacency_Matrix::Adjacency_Matrix(const std::string& filename)
	: a_matrix_{ std::vector<std::vector<int>>() }
{
	File_Handler f(filename, *this);
	if(!f.run())
		throw std::invalid_argument(f.what());
}

Adjacency_Matrix::Adjacency_Matrix(const size_t nodes)
	: a_matrix_{ std::vector<std::vector<int>>(nodes, std::vector<int>(nodes)) }
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
    return !(*this==rhs);
}

std::vector<int>& Adjacency_Matrix::operator[](const int index)
{
    return a_matrix_.at(index);
}

size_t Adjacency_Matrix::size() const
{
    return a_matrix_.size();
}

std::string Adjacency_Matrix::to_string() const
{
	auto output{ std::string() };
	int most_digits{ find_longest_number() };
	rows_to_string(output, most_digits);
	pretty_string(output);
	return output;
}

int Adjacency_Matrix::find_longest_number() const
{
	int most_digits{0}, digits;
	for(auto& rows: a_matrix_)
	{
		for(auto& cols: rows)
		{
			if( (digits = get_digits(cols)) > most_digits )
				most_digits = digits;
		}
	}
	return most_digits;
}

void Adjacency_Matrix::rows_to_string(std::string& output, int most_digits) const
{
	for(auto& rows: a_matrix_)
	{
		output += "| ";
		cols_to_string(output, rows, most_digits);
		output += "|\n";
	}
}

void Adjacency_Matrix::cols_to_string(std::string& output, const std::vector<int>& row, int most_digits) const
{
	for(auto& cols: row)
		output += std::string(most_digits - get_digits(cols),' ') 
				+ std::to_string(cols) + " ";
}

std::vector<std::vector<int>> Adjacency_Matrix::data() const
{
	return a_matrix_;
}

void Adjacency_Matrix::fill_with_random()
{
	std::generate(a_matrix_.begin(), a_matrix_.end(), [this](){
		return get_random_row();
	});
}

std::vector<int> Adjacency_Matrix::get_random_row()
{
	auto output{ std::vector<int>(a_matrix_.size()) };
	std::transform(output.begin(), output.end(), output.begin(), [](int node){
		return rand() % 100;
	});
	return output;
}

bool Adjacency_Matrix::load_from_file(std::fstream& in_file)
{
    try
    {
		load_data(in_file);
    }
    catch(const std::ifstream::failure& )
    {
        if(!in_file.eof())
			throw;
    }
	return true;
}

void Adjacency_Matrix::load_data(std::fstream& file)
{
	std::string line;
	std::getline(file, line);
	resize_matrix( parse_size_input(line) );
	for(auto& rows : a_matrix_)
	{
		std::getline(file, line);
		if(!file.eof())
			rows = line_to_vec(line);
	}
}

size_t Adjacency_Matrix::parse_size_input(std::string& size_input)
{
	size_t size;
	auto iss{ std::istringstream(size_input)};
	iss >> size;
	if(iss.fail())
		size = 0;
	return size;
}

void Adjacency_Matrix::resize_matrix(size_t size)
{
	a_matrix_.resize(size, std::vector<int>(size));
}

std::vector<int> Adjacency_Matrix::line_to_vec(std::string& line)
{
	auto output{ std::vector<int>() };
	std::stringstream iss(line);
	int value;
	while(iss >> value)
		output.push_back(value);
	
	return output;
}

void Adjacency_Matrix::pretty_string(std::string& str_matrix) const
{
	size_t line_len{ str_matrix.size()/ a_matrix_.size() };
	std::string dashes{ std::string(line_len - 1, '-') + "\n"};
	str_matrix.insert(0, dashes);
	str_matrix.append(dashes);
}

int Adjacency_Matrix::get_digits(const int number) const
{
	if(number == 0)
		return 1;

	auto pos_number{ abs(number) };
	auto digits{( log10((pos_number)) + 1 )};

	return number < 0 ? digits++ : digits;
}

std::vector<int> Adjacency_Matrix::get_neighbours(int node) const
{
	auto output{ std::vector<int>() };
	for(size_t i{0}; i < a_matrix_[node].size(); ++i)
	{
		if(a_matrix_[node][i] != 0)
			output.push_back(i);
	}
	return output;
}