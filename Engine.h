#pragma once

#include <vector>

#include <SDL2/SDL_thread.h>

#include "Space.h"

namespace phys
{
    class Engine
    {
    public:
        Engine(Space& space) : m_stop{ false }, m_pause{ false }, m_reverse{ 1 }, m_thread{ NULL}, m_space{ &space } {}

        void Start();
        void Stop();
        void Pause() { m_pause = true; }
        void Unpause() { m_pause = false; }
        void Reverse() { m_reverse = -1; }
        void Forward() { m_reverse = 1; }

    private:
        bool m_stop;
        bool m_pause;
        int m_reverse;
        SDL_Thread* m_thread;
        Space* m_space;
        static int Function(void* engine);
    };
}