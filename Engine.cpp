#include "Engine.h"

#include <vector>

#include <SDL2/SDL_thread.h>

#include "Clock.h"
#include "Particle.h"
#include "Vec.h"

namespace phys{ extern long long pframes; }

void phys::Engine::Start()
{
    stop = false;
    pause = false;
    m_thread = SDL_CreateThread(Function, "Phys Engine", (void*)this);
}

void phys::Engine::Stop()
{
    pause = true;
    stop = true;
    SDL_WaitThread(m_thread, NULL);
}

void phys::Engine::Step(double time)
{
    time *= speed;
    for(auto i = m_particles->begin(); i < m_particles->end(); i++)
    {
        for(auto j = i + 1; j != m_particles->end(); j++)
    	{
            Particle::Interact(*i, *j);
    	}
    }
    for(auto& i : *m_particles)
	{
		for(auto& j : *m_obstacles)
		{
            Particle::Interact(i, j);
		}
        i.Update(time);
	}
	for(auto& i : *m_cameras)
    {
		i.Update(time);
    }
}

int phys::Engine::Function(void* engine)
{
    Clock clock;
    #define ENGINE (*(Engine*)engine)
    while(!ENGINE.stop)
    {
        if(!ENGINE.pause)
        {
            clock.Resume();
            while(!ENGINE.pause)
            {
                double time = clock.Lap() * ENGINE.speed;
                for(auto i = ENGINE.m_particles->begin(); i < ENGINE.m_particles->end(); i++)
                {
    	            for(auto j = i + 1; j != ENGINE.m_particles->end(); j++)
    	            {
                        Particle::Interact(*i, *j);
    	            }
                }
                for(auto& i : *ENGINE.m_particles)
	            {
		            for(auto& j : *ENGINE.m_obstacles)
		            {
                        Particle::Interact(i, j);
		            }
                    i.Update(time);
	            }
	            for(auto& i : *ENGINE.m_cameras)
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