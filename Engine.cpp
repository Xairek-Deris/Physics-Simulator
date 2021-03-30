#include "Engine.h"

#include <SDL2/SDL.h>

#include "Clock.h"
#include "Space.h"

void phys::Engine::Start()
{
    m_stop = false;
    m_pause = false;
    m_thread = SDL_CreateThread(function, "Phys Engine", (void*)this);
}

void phys::Engine::Stop()
{
    m_pause = true;
    m_stop = true;
    int ret;
    SDL_WaitThread(m_thread, &ret);
}

static int phys::function(void* engine)
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
                pframes++;
            }
            clock.Stop();
        }
    }
    return 0;
}