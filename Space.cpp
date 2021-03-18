#include "Space.h"

ref_t phys::Space::Add_Particle(phys::Vector position, phys::Vector velocity, 
	double mass, double charge, double radius, double hardness)
{
    if(m_deleted_particles.size() > 0)
    {
        ref_t index = m_deleted_particles.back();
        m_deleted_particles.pop_back();
        m_particles[index] = phys::Particle(position, velocity, mass, charge, radius, hardness);
        return index;
    }
    if(m_particles.size() == m_particles.capacity())
        return -1;
    m_particles.push_back(phys::Particle(position, velocity, mass, charge, radius, hardness));
    return m_particles.size() - 1;
}

ref_t phys::Space::Add_Joint(ref_t particle_1, ref_t particle_2, 
    double tension, double length)
{
    if(m_deleted_joints.size() > 0)
    {
        ref_t index = m_deleted_joints.back();
        m_deleted_joints.pop_back();
        m_joints[index] = phys::Joint(m_particles.data() + particle_1, 
            m_particles.data() + particle_2, tension, length);
        return index;
    }
    if(m_joints.size() == m_joints.capacity())
        return -1;
    m_joints.push_back(phys::Joint(m_particles.data() + particle_1, 
        m_particles.data() + particle_2, tension, length));
    return m_joints.size() - 1;
}

void phys::Space::Remove_Particle(ref_t reference)
{
    m_deleted_particles.push_back(reference);
    m_particles[reference] = phys::Particle(phys::Vector{ 0, 0, 0 }, 
        phys::Vector{ 0, 0, 0 }, 0, 0, 0, 0);
}

void phys::Space::Remove_Joint(ref_t reference)
{
    m_deleted_joints.push_back(reference);
    m_joints[reference] = phys::Joint(m_particles.data(), m_particles.data(), 0, 0);
}