#include "Engine.h"

#include <vector>

#include "Clock.h"
#include "Particle.h"
#include "Vec.h"

namespace phys{ extern long long pframes; }

void phys::Engine::Start()
{
    m_stop = false;
    pause = false;
    m_thread.Start(Function, (void*)this);
}

void phys::Engine::Stop()
{
    pause = true;
    m_stop = true;
    m_thread.Wait();
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
    while(!ENGINE.m_stop)
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