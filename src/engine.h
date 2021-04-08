#pragma once

#include <vector>

#include "Physics/particle.h"
#include "Physics/camera.h"
#include "Display/thread.h"

namespace phys
{
    //Physics engine that can be run on a separate thread easily
    //Safe to move but not safe to copy
    class Engine
    {
    public:
        //p = particle vector, o = obstacle vector, c = camera vector
        Engine(std::vector<Particle>& p, std::vector<Particle>& o, 
                std::vector<Camera>& c) 
        : stop_{ true }, pause_{ true }, speed_{ 1 },
            particles_{ &p }, obstacles_{ &o}, cameras_{ &c } 
        {}

        ~Engine() { if(!stop_) stop(); }

        //Starts the engine on a separate thread.
        void start()
        {
            stop_ = false;
            pause_ = false;
            thread_.start(thread_function, "Engine Thread", this);
        }

        //Stops the engine and waits for the thread to end
        void stop()
        {
            pause_ = true;
            stop_ = true;
            thread_.wait();
        }

        //Pauses thread_function() without terminating the thread
        void pause()    { pause_ = true; }
        void unpause()  { pause_ = false; }
        bool stopped()  { return stop_; }
        bool paused()   { return pause_; }

        //Multiplier for a running engine. Doesn't affect step
        double& speed() { return speed_; }

        //Updates all particles, obstacles, and cameras for the interval (t)
        void step(double t);

    private:
        bool stop_;
        bool pause_;
        double speed_;

        disp::Thread thread_;

        std::vector<Particle>* particles_;
        std::vector<Particle>* obstacles_;
        std::vector<Camera>* cameras_;

        //Updates all particles, obstacles, and cameras continuously
        static int thread_function(void* e);
    };
}