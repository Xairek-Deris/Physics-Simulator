#include "Engine.h"

#include <vector>

#include <SDL2/SDL_thread.h>

#include "Clock.h"
#include "Particle.h"
#include "Vec.h"

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
    SDL_WaitThread(m_thread, NULL);
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
                double time = clock.Lap() * ENGINE->m_reverse;
                for(auto i = ENGINE->m_particles->begin(); i < ENGINE->m_particles->end(); i++)
                {
    	            for(auto j = i + 1; j != ENGINE->m_particles->end(); j++)
    	            {
                        Particle::Interact(*i, *j);
    	            }
                }
                for(auto& i : *ENGINE->m_particles)
	            {
		            for(auto& j : *ENGINE->m_obstacles)
		            {
                        Particle::Interact(i, j);
		            }
                    i.Update(time);
	            }
	            for(auto& i : *ENGINE->m_cameras)
                {
		            i.Update(time);
                }
                phys::pframes++;
            }           
            clock.Stop();
        }
    }
    return 0;
}