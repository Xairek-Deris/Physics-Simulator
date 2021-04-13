#include "clock.h"

phys::Clock::Clock()
: paused_{ false }
{
    start_point_ = std::chrono::high_resolution_clock::now();
    lap_point_ = start_point_;
}

void phys::Clock::start()
{
    start_point_ = std::chrono::high_resolution_clock::now();
    lap_point_ = start_point_;
}

//Stops the clock. Use start to restart or resume to continue.
//Any lap and time calls will treat this time as the current time.
double phys::Clock::stop()
{
    stop_point_ = std::chrono::high_resolution_clock::now();
    paused_ = true;

    auto start = std::chrono::time_point_cast
                    <std::chrono::microseconds>(start_point_)
                    .time_since_epoch().count();

    auto end = std::chrono::time_point_cast
                    <std::chrono::microseconds>(stop_point_)
                    .time_since_epoch().count();

    return (end - start) * 1e-6;
}

//Continues from last stop point
void phys::Clock::resume()
{
    if(paused_)
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto duration = current_time - stop_point_;
        start_point_ += duration;
        lap_point_ += duration;
        paused_ = false;
    }
}

//Returns the total run-time since start
double phys::Clock::time()
{
    if(!paused_)
        stop_point_ = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast
                    <std::chrono::microseconds>(start_point_)
                    .time_since_epoch().count();

    auto end = std::chrono::time_point_cast
                    <std::chrono::microseconds>(stop_point_)
                    .time_since_epoch().count();

    return (end - start) * 1e-6;
}

//Returns time elapsed since last lap, or from start if no previous lap.
double phys::Clock::lap()
{
    if(!paused_)
        stop_point_ = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast
                    <std::chrono::microseconds>(lap_point_)
                    .time_since_epoch().count();

    auto end = std::chrono::time_point_cast
                <std::chrono::microseconds>(stop_point_)
                .time_since_epoch().count();
    lap_point_ = stop_point_;
    return (end - start) * 1e-6;
}