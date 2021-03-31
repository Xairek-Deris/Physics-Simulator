#include "Space.h"

#include <vector>

#include "Camera.h"
#include "Particle.h"

void phys::Space::Update(double time)
{
	for(auto i = particles.begin(); i < particles.end(); i++)
    	for(auto j = i + 1; j != particles.end(); j++)
    	{
        	Particle::Electrify(*i, *j);
        	Particle::Gravitate(*i, *j);
        	Particle::Collide(*i, *j);
    	}
    for(auto& i : particles)
	{
		for(auto& j : obstacles)
		{
			Particle::Electrify(i, j);
			Particle::Gravitate(i, j);
        	Particle::Collide(i, j);
		}
        i.Update(time);
	}
	for(auto& i : cameras)
		i.Update(time);
}
