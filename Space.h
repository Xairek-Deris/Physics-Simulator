#include <vector>

#include <string>

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
        }

        void Update(double time);

        phys::Particle* Get_Particle(ref_t reference) { return m_particles.data() + reference; }
        phys::Joint* Get_Joint(ref_t reference) { return m_joints.data() + reference; }

        ref_t Add_Particle(Particle& particle);
        ref_t Add_Joint(Joint& joint);

        void Remove_Particle(ref_t reference);
        void Remove_Joint(ref_t reference);

        int Load(std::string filename);
        int Save(std::string filename);

    private:
        std::vector<phys::Particle> m_particles;
        std::vector<phys::Joint> m_joints;

        std::vector<ref_t> m_deleted_particles;
        std::vector<ref_t> m_deleted_joints;
    };
}
//impliment update function