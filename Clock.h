#include <chrono>

namespace phys
{
class Clock
    {
    public:
        Clock()
        : m_paused{ false }
        {
            m_start_point = std::chrono::high_resolution_clock::now();
            m_lap_point = m_start_point;
        }

        void Start()
        {
            m_start_point = std::chrono::high_resolution_clock::now();
            m_lap_point = m_start_point;
        }

        double Stop()
        {
            m_stop_point = std::chrono::high_resolution_clock::now();
            m_paused = true;
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_point).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_stop_point).time_since_epoch().count();
            return (end - start) * 1e-6;
        }

        void Resume()
        {
            if(m_paused)
            {
                auto current_time = std::chrono::high_resolution_clock::now();
                auto duration = current_time - m_stop_point;
                m_start_point += duration;
                m_lap_point += duration;
                m_paused = false;
            }
        }

        double Time()
        {
            if(!m_paused)
                m_stop_point = std::chrono::high_resolution_clock::now();
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_point).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_stop_point).time_since_epoch().count();
            return (end - start) * 1e-6;
        }

        double Lap()
        {
            if(!m_paused)
                m_stop_point = std::chrono::high_resolution_clock::now();
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_lap_point).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_stop_point).time_since_epoch().count();
            m_lap_point = m_stop_point;
            return (end - start) * 1e-6;
        }

    private:
        std::chrono::time_point< std::chrono::high_resolution_clock> m_start_point;
        std::chrono::time_point< std::chrono::high_resolution_clock> m_lap_point;
        std::chrono::time_point< std::chrono::high_resolution_clock> m_stop_point;
        bool m_paused;
    };
}