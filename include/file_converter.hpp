#pragma once

#include <fstream>
#include <string>

namespace utils {
class file_converter
{
   public:
    int convert(const std::string& file_in, const std::string& file_out);

   private:
    void error_exit(const std::string& msg);
    int header_get_size(std::ifstream& file);
    int value_digits(int val);
};
}  // namespace utils