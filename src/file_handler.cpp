#include "../include/file_handler.hpp"

File_Handler::File_Handler(std::string filepath, Adjacency_Matrix& matrix)
    : filepath_ {filepath}, matrix_ {matrix}
{
}

bool File_Handler::run()
{
    std::fstream file;
    file.exceptions(std::fstream::failbit | std::fstream::badbit);
    try
    {
        file.open(filepath_);
        matrix_.load_from_file(file);
    } catch (const std::ios_base::failure&)
    {
        error_ = "Error: Could not open the file specified.";
        return false;
    } catch (const std::invalid_argument&)
    {
        error_ = "Error: Could not read from the file specified.";
        return false;
    }
    return true;
}

std::string File_Handler::what() const { return error_; }