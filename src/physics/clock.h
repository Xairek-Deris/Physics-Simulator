#pragma once

#include <chrono>

namespace phys
{
    //Clock with start, stop, and lap capabilities.
    //Time starts upon construction. Safe to move or copy.
    class Clock
    {
    public:
        Clock();
        
        void start();

        //Stops the clock. Use start to restart or resume to continue.
        //Any lap and time calls will treat this time as the current time.
        double stop();

        //Continues from last stop point
        void resume();

        //Returns the total run-time since start
        double time();

        //Returns time elapsed since last lap, or from start if no previous lap.
        double lap();

    private:
        bool paused_;

        std::chrono::time_point
            < std::chrono::high_resolution_clock> start_point_;

        std::chrono::time_point
            < std::chrono::high_resolution_clock> lap_point_;

        std::chrono::time_point
            < std::chrono::high_resolution_clock> stop_point_;
    };
}