#include "../include/menu_handler.hpp"
#include "../include/timer.hpp"

#include <iostream>
#include <string>

void Menu::run(const std::vector<std::string>& subtitles,
               const std::string title)
{
    handle_input(subtitles, title);
}

void Menu::draw_menu(const std::vector<std::string>& subtitles,
                     const std::string title) const
{
    clear_term();
    int line_len {longest_subtitle(subtitles)};
    int total_line_len = line_len + format_chars;

    draw_title(title, total_line_len);
    draw_body(subtitles, line_len);

    std::cout << std::string(total_line_len, '-') << std::endl;
    std::cout << "\n Your choice >> ";
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

int Menu::longest_subtitle(const std::vector<std::string>& subtitles) const
{
    auto max_el = std::max_element(subtitles.begin(), subtitles.end(),
                                   [&](std::string lhs, std::string rhs) {
                                       return lhs.size() < rhs.size();
                                   });
    return (*max_el).size();
}

void Menu::draw_title(const std::string& title, const unsigned line_len) const
{
    unsigned dash_count {line_len - (unsigned)title.size() - 2};
    auto dashes {std::string((int)dash_count / 2, '-')};
    auto title_string {std::string(dashes + " " + title + " " + dashes)};

    if (dash_count % 2 == 0)
        std::cout << title_string << std::endl;
    else
        std::cout << title_string << "-" << std::endl;
}

void Menu::draw_body(const std::vector<std::string>& subtitles,
                     const unsigned max_line) const
{
    for (size_t i {1}; i <= subtitles.size(); ++i)
        std::cout << align_line(subtitles[i - 1], i, max_line);
}

std::string Menu::align_line(const std::string& line, const unsigned line_no,
                             const unsigned max_len) const
{
    return std::string("| " + std::to_string(line_no) + ") " + line +
                       std::string(max_len - line.size(), ' ') + " |\n");
}

void Menu::handle_input(const std::vector<std::string>& subtitles,
                        std::string title)
{
    int choice = 4;
    bool exit  = false;
    while (!exit)
    {
        draw_menu(subtitles, title);
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                secure_read_double(tsp_api.time_limit_);
                break;
            }
            case 2:
            {
                secure_read_double(tsp_api.temp_factor_);
                break;
            }
            case 3:
            {
                load_from_file(get_filename());
                break;
            }
            case 4:
            {
                if (tsp_api.is_loaded)
                    algorithm_menu();
                else
                {
                    std::cout << "\n Error: No graph data.";
                    wait_for_reaction();
                }
                break;
            }
            default:
            {
                exit = true;
                break;
            }
        }
    }
}

void Menu::algorithm_menu()
{
    int choice                         = 4;
    bool exit                          = false;
    std::vector<std::string> subtitles = {"SA - Linear cooling",
                                          "SA - Logarithmic cooling",
                                          "SA - Exponential cooling",
                                          "Tabu Search - Swap",
                                          "Tabu Search - Swap and Reverse",
                                          "Tabu Search - Insertion",
                                          "Previous"};
    while (!exit)
    {
        draw_menu(subtitles, "Algorithms");
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                clear_term();
                std::cout << tsp_api.simulated_annealing().to_string();
                wait_for_reaction();
                break;
            }
            case 2:
            {
                clear_term();
                std::cout
                    << tsp_api
                           .simulated_annealing(
                               tsp_approx::sim_annealing::logarithmical_cooling)
                           .to_string();
                wait_for_reaction();
                break;
            }
            case 3:
            {
                clear_term();
                std::cout
                    << tsp_api
                           .simulated_annealing(
                               tsp_approx::sim_annealing::exponential_cooling)
                           .to_string();
                wait_for_reaction();
                break;
            }
            case 4:
            {
                clear_term();
                std::cout << tsp_api.tabu_search().to_string();
                wait_for_reaction();
                break;
            }
            case 5:
            {
                clear_term();
                std::cout << tsp_api
                                 .tabu_search(
                                     tsp_approx::tabu_search::swap_n_reverse)
                                 .to_string();
                wait_for_reaction();
                break;
            }
            case 6:
            {
                clear_term();
                std::cout << tsp_api
                                 .tabu_search(
                                     tsp_approx::tabu_search::insertion)
                                 .to_string();
                wait_for_reaction();
                break;
            }
            default:
            {
                exit = true;
                break;
            }
        }
    }
}

void Menu::load_from_file(const std::string& filename)
{
    try
    {
        tsp_api.load_from_file(filename);
    } catch (const std::invalid_argument& e)
    {
        std::cout << "\n Error >> " << e.what();
        wait_for_reaction();
    }
}

void Menu::wait_for_reaction()
{
    getchar();
    getchar();
}

std::string Menu::get_filename()
{
    std::string filename;
    std::cout << " Enter the path to a file >> ";
    std::cin >> filename;
    return filename;
}

double Menu::get_double()
{
    double amount;
    std::string input;
    std::cout << " Enter the amount >> ";
    std::cin >> input;
    amount = strtod(input.c_str(), nullptr);
    return amount;
}

void Menu::secure_read_double(double& amount)
{
    try
    {
        amount = get_double();
    } catch (const std::invalid_argument& e)
    {
        std::cout << "\n" << e.what();
    }
}