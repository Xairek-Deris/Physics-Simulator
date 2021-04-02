#pragma once

#include <vector>

#include <SDL2/SDL_thread.h>

#include "Particle.h"
#include "Camera.h"

namespace phys
{
    class Engine
    {
    public:
        Engine(std::vector<Particle>& particles, std::vector<Particle>& obstacles, std::vector<Camera>& cameras) 
        : m_stop{ false }, m_pause{ false }, m_reverse{ 1 }, m_thread{ NULL}, m_particles{ &particles }, m_obstacles{ &obstacles}, m_cameras{ &cameras } {}

        void Start();
        void Stop();
        void Step(double time);
        void Pause() { m_pause = true; }
        void Unpause() { m_pause = false; }
        void Reverse() { m_reverse = -1; }
        void Forward() { m_reverse = 1; }

    private:
        bool m_stop;
        bool m_pause;
        int m_reverse;
        SDL_Thread* m_thread;
        std::vector<Particle>* m_particles;
        std::vector<Particle>* m_obstacles;
        std::vector<Camera>* m_cameras;
        static int Function(void* engine);
    };
}