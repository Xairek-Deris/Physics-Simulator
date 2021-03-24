#include <chrono>

class Clock
{
public:
    Clock()
    {
        m_start_point = std::chrono::high_resolution_clock::now();
        m_lap_point = m_start_point;
    }

    double Time()
    {
        auto end_point = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_point).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_point).time_since_epoch().count();
        return (end - start) * 1e-6;
    }

    double Lap()
    {
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_lap_point).time_since_epoch().count();
        m_lap_point = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_lap_point).time_since_epoch().count();
        return (end - start) * 1e-6;
    }
    /*
    double Pause()
    {
        m_pause_point = std::chrono::high_resolution_clock::now();
    }
    */

private:
    std::chrono::time_point< std::chrono::high_resolution_clock> m_start_point;
    std::chrono::time_point< std::chrono::high_resolution_clock> m_lap_point;
    //std::chrono::time_point< std::chrono::high_resolution_clock> m_pause_point;
};