#pragma once

#include "adjacency_matrix.hpp"
#include "path.hpp"
#include "timer.hpp"
#include "tsp.hpp"

#include <fstream>
#include <string>
#include <vector>

class Menu {
   public:
    Menu()        = default;
    Menu& operator=(const Menu& rhs) = delete;

    ~Menu() = default;

    void run(const std::string subtitles[], size_t size,
             const std::string title);

   private:
    const int format_chars = 7;  // = | 1) "..." |
    tsp tsp_api;

    void draw_menu(const std::string subtitles[], size_t size,
                   const std::string title) const;
    void draw_extras() const;
    void draw_title(const std::string& title, const unsigned max_line) const;
    void draw_body(const std::string subtitles[], size_t size,
                   const unsigned max_line) const;
    std::string align_line(const std::string& line, const unsigned line_no,
                           const unsigned max_len) const;
    void clear_term() const;
    int longest_subtitle(const std::string subtitles[], size_t size) const;

    void handle_input(const std::string subtitles[], size_t size,
                      std::string title);
    std::string get_filename();
    double get_double();
    void secure_read_double(double&);
    void load_from_file(const std::string& filename);
    void wait_for_reaction();

    void algorithm_menu();
};