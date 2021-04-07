#include "engine.h"

#include <vector>

#include "Physics/camera.h"
#include "Physics/particle.h"
#include "Physics/clock.h"

//temporary frame count for testing
extern long long pframes;

void phys::Engine::step(double t)
{
    for(auto i = particles_->begin(); i < particles_->end(); i++)
    {
        for(auto j = i + 1; j != particles_->end(); j++)
    	{
            Particle::interact(*i, *j);
    	}
    }

    for(auto& i : *particles_)
	{
		for(auto& j : *obstacles_)
		{
            Particle::interact(i, j);
		}
        
        i.update(t);
	}

	for(auto& i : *cameras_)
    {
		i.update(t);
    }
}

int phys::Engine::thread_function(void* e)
{
    #define ENGINE (*(Engine*)e)
    Clock clock;

    while(!ENGINE.stop_)
    {
        if(!ENGINE.pause_)
        {
            clock.resume();
            while(!ENGINE.pause_)
            {
                double time = clock.lap() * ENGINE.speed_;
                ENGINE.step(time);
                pframes++;
            }           
            clock.stop();
        }
    }

    return 0;
}