#pragma once

#include <vector>

#include <SDL2/SDL_thread.h>

#include "Camera.h"
#include "Thread.h"
#include "Particle.h"

namespace phys
{
    class Engine
    {
    public:
        Engine(std::vector<Particle>& particles, std::vector<Particle>& obstacles, std::vector<Camera>& cameras) 
        : m_stop{ false }, pause{ false }, speed{ 1 }, m_thread{ "Physics Thread" }, m_particles{ &particles }, m_obstacles{ &obstacles}, m_cameras{ &cameras } {}

        ~Engine() { if(!m_stop) Stop(); }

        void Start();
        void Stop();
        void Step(double time);
        bool pause;
        double speed;
    private:

        phys::Thread m_thread;
        std::vector<Particle>* m_particles;
        std::vector<Particle>* m_obstacles;
        std::vector<Camera>* m_cameras;
        bool m_stop;
        static int Function(void* engine);
    };
}