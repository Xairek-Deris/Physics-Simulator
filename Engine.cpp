#include "Engine.h"

#include <SDL2/SDL_thread.h>

#include "Clock.h"
#include "Space.h"

namespace phys{ extern long long pframes; }

void phys::Engine::Start()
{
    m_stop = false;
    m_pause = false;
    m_thread = SDL_CreateThread(Function, "Phys Engine", (void*)this);
}

void phys::Engine::Stop()
{
    m_pause = true;
    m_stop = true;
    int ret;
    SDL_WaitThread(m_thread, &ret);
}

int phys::Engine::Function(void* engine)
{
    Clock clock;
    #define ENGINE ((Engine*)engine)
    while(!ENGINE->m_stop)
    {
        if(!ENGINE->m_pause)
        {
            clock.Resume();
            while(!ENGINE->m_pause)
            {
                ENGINE->m_space->Update(clock.Lap());
                phys::pframes++;
            }
            clock.Stop();
        }
    }
    return 0;
}