#include "Space.h"

#include <stdio.h>

void phys::Space::Update(double time)
{
    for(auto i = m_particles.begin(); i != m_particles.end(); i++)
        for(auto j = i + 1; j != m_particles.end(); j++)
        {
            Electric(*i, *j);
            Gravitate(*i, *j);
            Collide(*i, *j);
        }
    
    for(auto& i : m_joints)
        i.Apply(m_particles.data());
    
    for(auto& i : m_particles)
        i.Update(time);
}

ref_t phys::Space::Add_Particle(Particle& particle)
{
    if(m_deleted_particles.size() > 0)
    {
        ref_t index = m_deleted_particles.back();
        m_deleted_particles.pop_back();
        m_particles[index] = particle;
        return index;
    }
    if(m_particles.size() == m_particles.capacity())
        return -1;
    m_particles.push_back(particle);
    return m_particles.size() - 1;
}

ref_t phys::Space::Add_Joint(Joint& joint)
{
    if(m_deleted_joints.size() > 0)
    {
        ref_t index = m_deleted_joints.back();
        m_deleted_joints.pop_back();
        m_joints[index] = joint;
        return index;
    }
    if(m_joints.size() == m_joints.capacity())
        return -1;
    m_joints.push_back(joint);
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
    m_joints[reference] = Joint(0, 0, 0, 0);
}

int phys::Space::Load(std::string filename)
{
    FILE* file = fopen(filename.c_str(), "r");
    if(file == nullptr)
        return -1;

    unsigned count;

    fread(&count, sizeof(count), 1, file);
    if(count > m_particles.size())
        m_particles.reserve(count);
    fread(m_particles.data(), sizeof(Particle), count, file);

    fread(&count, sizeof(count), 1, file);
    if(count > m_joints.size())
        m_joints.reserve(count);
    fread(m_joints.data(), sizeof(Joint), count, file);

    fread(&count, sizeof(count), 1, file);
    m_deleted_particles.reserve(count + 10);
    fread(m_deleted_particles.data(), sizeof(ref_t), count, file);

    fread(&count, sizeof(count), 1, file);
    m_deleted_joints.reserve(count + 10);
    fread(m_deleted_joints.data(), sizeof(ref_t), count, file);

    fclose(file);

    return 0;
}

int phys::Space::Save(std::string filename)
{
    FILE* file = fopen(filename.c_str(), "w");
    if(file == nullptr)
        return -1;
    
    unsigned count = m_particles.size();
    fwrite(&count, sizeof(count), 1, file);
    fwrite(m_particles.data(), sizeof(Particle), count, file);

    count = m_joints.size();
    fwrite(&count, sizeof(count), 1, file);
    fwrite(m_joints.data(), sizeof(Joint), count, file);

    count = m_deleted_particles.size();
    fwrite(&count, sizeof(count), 1, file);
    fwrite(m_deleted_particles.data(), sizeof(ref_t), count, file);

    count = m_deleted_joints.size();
    fwrite(&count, sizeof(count), 1, file);
    fwrite(m_deleted_joints.data(), sizeof(ref_t), count, file);

    fclose(file);

    return 0;
}