#include "Space.h"

#include <string>
#include <vector>

#include <stdio.h>

#include "Particle.h"

int phys::Space::Load(const std::string& filename)
{
	FILE* file = fopen(filename.c_str(), "r");
	if(file == NULL)
		return -1;
	int size;
	fread(&size, sizeof(size), 1, file);
	if(size > particles.capacity())
		particles.reserve(size + 5);
	fread(particles.data(), sizeof(Particle), size, file);
	return 0;
}

int phys::Space::Save(const std::string& filename)
{
	FILE* file = fopen(filename.c_str(), "w");
	if(file == NULL)
		return -1;
	int size = particles.size();
	fwrite(&size, sizeof(size), 1, file);
	fwrite(particles.data(), sizeof(Particle), size, file);
	return 0;
}

void phys::Space::Update(double time)
{
	for(auto i = particles.begin(); i != particles.end(); i++)
    	for(auto j = i + 1; j != particles.end(); j++)
    	{
        	Particle::Electrify(*i, *j);
        	Particle::Gravitate(*i, *j);
        	Particle::Collide(*i, *j);
    	}
    for(auto& i : particles)
        i.Update(time);
}
