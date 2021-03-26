#pragma once

#include "Clock.h"
#include "Space.h"

namespace phys
{
    //Only to be used on a separate thread.
    class Engine : public Space
    {
    public:
        Engine(int num_particles = 5) : m_stop{ false }, m_stopped{ true }, m_pause{ false }, m_paused{ true }, Space(num_particles){}
        ~Engine() { Stop(); }
        void Run();
        void Stop() { m_stop = true; m_pause = true; m_clock.Stop(); }
        void Pause() { m_pause = true; m_clock.Stop(); }
        void Unpause() { m_pause = false; m_clock.Resume(); }
        bool Stopped() { return m_stopped; }
        bool Paused() { return m_paused; }
        
    private:
        bool m_stop;
        bool m_stopped;
        bool m_pause;
        bool m_paused;
        Clock m_clock;
    };
}