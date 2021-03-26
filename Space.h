#include <string>
#include <vector>

#include "Particle.h"
#include "Vec.h"

namespace phys
{
    struct Space
    {
        Space(int num_particles = 5)
        {
            particles.reserve(num_particles);
        }

        int Load(std::string& filename);
        int Save(std::string& filename);
        void Update(double time);

        std::vector<Particle> particles;
    };
}