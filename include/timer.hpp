#pragma once

#include <chrono>

#include <functional>
#include <iostream>
#include <optional>

template <typename T, typename... Args>
class Timer {
   public:
    Timer() = delete;

    Timer(std::function<T(Timer<T, Args...>*, Args...)> fnc_to_measure)
        : fnc_to_measure_{fnc_to_measure} {};

    ~Timer()       = default;
    Timer& operator=(const Timer& rhs) = default;

    double run(Args... args);
    double get_elapsed();

    T get_output();

   private:
    std::function<T(Timer<T, Args...>*, Args...)> fnc_to_measure_;
    std::optional<T> alg_value;

    std::chrono::high_resolution_clock::time_point start_time_;

    void start_counter();
};

template <typename T, typename... Args>
double Timer<T, Args...>::run(Args... args)
{
    start_counter();
    alg_value = fnc_to_measure_(this, args...);
    return get_elapsed();
}

template <typename T, typename... Args>
void Timer<T, Args...>::start_counter()
{
    start_time_ = std::chrono::high_resolution_clock::now();
}

template <typename T, typename... Args>
double Timer<T, Args...>::get_elapsed()
{
    auto end_time{std::chrono::high_resolution_clock::now()};
    std::chrono::duration<double, std::milli> duration{end_time - start_time_};
    return duration.count();
}

template <typename T, typename... Args>
T Timer<T, Args...>::get_output()
{
    if (alg_value.has_value())
        return alg_value.value();
    else
        throw std::invalid_argument("Timed function does not return a value.");
}