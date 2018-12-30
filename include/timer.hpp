#pragma once

#include <chrono>

#include <functional>
#include <iostream>
#include <optional>

template <typename T, typename... Args>
class Timer
{
   public:
    Timer() = delete;

    Timer(std::function<T(Timer<T, Args...>*, Args...)> fnc_to_measure)
        : fnc_to_measure_ {fnc_to_measure}, time_limit_ {0} {};

    Timer(std::function<T(Timer<T, Args...>*, Args...)> fnc_to_measure,
          double time_limit)
        : fnc_to_measure_ {fnc_to_measure}, time_limit_ {time_limit} {};

    ~Timer() = default;

    Timer& operator=(const Timer&) = default;
    Timer& operator=(Timer&&) = default;

    Timer(Timer&&) = default;
    Timer(Timer&)  = default;

    double run(Args... args);
    double get_elapsed();
    double is_finished();

    bool reached_checkpoint();

    T get_output();

   private:
    std::function<T(Timer<T, Args...>*, Args...)> fnc_to_measure_;
    std::optional<T> alg_value;
    double time_limit_;

    /* Variables needed to run the checkpoint printing. */
    int checkpoint_counter_   = 1;
    int number_of_checkpoints = 5;
    /****************************************************/

    std::chrono::high_resolution_clock::time_point start_time_;

    void start_counter();
};

template <typename T, typename... Args>
double Timer<T, Args...>::run(Args... args)
{
    start_counter();
    alg_value = fnc_to_measure_(this, args...);
    auto end_time {std::chrono::high_resolution_clock::now()};
    std::chrono::duration<double, std::milli> duration {end_time - start_time_};
    return duration.count();
}

template <typename T, typename... Args>
void Timer<T, Args...>::start_counter()
{
    start_time_ = std::chrono::high_resolution_clock::now();
}

template <typename T, typename... Args>
double Timer<T, Args...>::get_elapsed()
{
    auto end_time {std::chrono::high_resolution_clock::now()};
    std::chrono::duration<double, std::milli> duration {end_time - start_time_};
    return duration.count();
}

template <typename T, typename... Args>
double Timer<T, Args...>::is_finished()
{
    return get_elapsed() < time_limit_;
}

template <typename T, typename... Args>
T Timer<T, Args...>::get_output()
{
    if (alg_value.has_value())
        return alg_value.value();
    else
        throw std::invalid_argument("Timed function does not return a value.");
}

template <typename T, typename... Args>
bool Timer<T, Args...>::reached_checkpoint()
{
    if (get_elapsed() >
        (checkpoint_counter_ / static_cast<double>(number_of_checkpoints)) *
            time_limit_)
    {
        ++checkpoint_counter_;
        return true;
    }
    return false;
}