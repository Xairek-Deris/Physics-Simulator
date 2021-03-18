#include <vector>

#include "Particle.h"
#include "Joint.h"
#include "Vec.h"

typedef int ref_t;

namespace phys
{
    class Space
    {
    public:
        Space(unsigned particles, unsigned joints) 
        { 
            m_particles.reserve(particles); 
            m_joints.reserve(joints);
            //first particle is blank to allow deleted joints to reference it
            m_particles.push_back(phys::Particle(phys::Vector{ 0, 0, 0 }, 
                phys::Vector{ 0, 0, 0 }, 0, 0, 0, 0));
        }

        void update(double seconds);

        phys::Particle* Particle(ref_t reference) { return &m_particles[reference]; }
        phys::Joint* Joint(ref_t reference) { return &m_joints[reference]; }

        ref_t Add_Particle(phys::Vector position, phys::Vector velocity, 
		    double mass, double charge, double radius, double hardness);
        ref_t Add_Joint(ref_t particle_1, ref_t particle_2, double tension, double length);

        void Remove_Particle(ref_t reference);
        void Remove_Joint(ref_t reference);

    private:
        std::vector<phys::Particle> m_particles;
        std::vector<phys::Joint> m_joints;

        std::vector<ref_t> m_deleted_particles;
        std::vector<ref_t> m_deleted_joints;
    };
}
//TODO add loading and unloading functions
//impliment update function