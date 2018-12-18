#include "../include/menu_handler.hpp"
#include "../include/timer.hpp"

#include <iostream>
#include <string>

void Menu::run(const std::string subtitles[], size_t size,
               const std::string title)
{
    handle_input(subtitles, size, title);
}

void Menu::draw_menu(const std::string subtitles[], size_t size,
                     const std::string title) const
{
    clear_term();
    int line_len{longest_subtitle(subtitles, size)};
    int total_line_len = line_len + format_chars;

    draw_title(title, line_len + format_chars);
    draw_body(subtitles, size, line_len);

    std::cout << std::string(line_len + format_chars, '-') << std::endl;
    std::cout << "\n Twoj wybor >> ";
}

void Menu::draw_extras() const {}

void Menu::clear_term() const
{
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("CLS");
#endif
}

int Menu::longest_subtitle(const std::string subtitles[], size_t size) const
{
    unsigned max_len{0};
    for (size_t i{0}; i < size; ++i) {
        if (max_len < subtitles[i].size())
            max_len = subtitles[i].size();
    }
    return max_len;
}

void Menu::draw_title(const std::string& title, const unsigned line_len) const
{
    unsigned dash_count{line_len - (unsigned)title.size() - 2};
    auto dashes{std::string((int)dash_count / 2, '-')};
    auto title_string{std::string(dashes + " " + title + " " + dashes)};

    if (dash_count % 2 == 0)
        std::cout << title_string << std::endl;
    else
        std::cout << title_string << "-" << std::endl;
}

void Menu::draw_body(const std::string subtitles[], size_t size,
                     const unsigned max_line) const
{
    for (size_t i{1}; i <= size; ++i)
        std::cout << align_line(subtitles[i - 1], i, max_line);
}

std::string Menu::align_line(const std::string& line, const unsigned line_no,
                             const unsigned max_len) const
{
    return std::string("| " + std::to_string(line_no) + ") " + line +
                       std::string(max_len - line.size(), ' ') + " |\n");
}

void Menu::handle_input(const std::string subtitles[], size_t size,
                        std::string title)
{
    int choice = 4;
    bool exit  = false;
    while (!exit) {
        draw_menu(subtitles, size, title);
        std::cin >> choice;
        switch (choice) {
            case 1: {
                secure_read_double(tsp_api.time_limit_);
                break;
            }
            case 2: {
                secure_read_double(tsp_api.temp_factor_);
                break;
            }
            case 3: {
                load_from_file(get_filename());
                break;
            }
            case 4: {
                algorithm_menu();
                break;
            }
            default: {
                exit = true;
                break;
            }
        }
    }
}

void Menu::algorithm_menu()
{
    int choice              = 4;
    bool exit               = false;
    std::string subtitles[] = {"Liniowe", "Logarytmiczne", "Wykladnicze",
                               "Powrot"};
    while (!exit) {
        draw_menu(subtitles, 4, "Typ chlodzenia");
        std::cin >> choice;
        switch (choice) {
            case 1: {
                clear_term();
                std::cout << tsp_api.simulated_annealing().to_string();
                wait_for_reaction();
                break;
            }
            case 2: {
                clear_term();
                std::cout
                    << tsp_api
                           .simulated_annealing(
                               tsp_approx::sim_annealing::logarithmical_cooling)
                           .to_string();
                wait_for_reaction();
                break;
            }
            case 3: {
                clear_term();
                std::cout
                    << tsp_api
                           .simulated_annealing(
                               tsp_approx::sim_annealing::exponential_cooling)
                           .to_string();
                wait_for_reaction();
                break;
            }
            default: {
                exit = true;
                break;
            }
        }
    }
}

void Menu::load_from_file(const std::string& filename)
{
    try {
        tsp_api.load_from_file(filename);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "\n Error >> " << e.what();
    }
    wait_for_reaction();
}

void Menu::wait_for_reaction()
{
    getchar();
    getchar();
}

std::string Menu::get_filename()
{
    std::string filename;
    std::cout << " Wprowadz sciezke do pliku >> ";
    std::cin >> filename;
    return filename;
}

double Menu::get_double()
{
    double amount;
    std::string input;
    std::cout << " Wprowadz liczbe >> ";
    std::cin >> input;
    amount = strtod(input.c_str(), nullptr);
    return amount;
}

void Menu::secure_read_double(double& amount)
{
    try {
        amount = get_double();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "\n" << e.what();
    }
}