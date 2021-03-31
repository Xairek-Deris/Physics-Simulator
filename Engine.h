#pragma once

#include <vector>

#include <SDL2/SDL_thread.h>

#include "Space.h"

namespace phys
{
    class Engine
    {
    public:
        Engine(Space& space) : m_stop{ false }, m_pause{ false }, m_thread{ NULL}, m_space{ &space } {}

        void Start();
        void Stop();
        void Pause() {m_pause = true;}
        void Unpause() {m_pause = false;}

    private:
        bool m_stop;
        bool m_pause;
        SDL_Thread* m_thread;
        Space* m_space;
        static int Function(void* engine);
    };
}