#pragma once

#include "vector.h"

namespace phys
{

    //2d camera used until 3d rendering is possible. Can be given a velocity
    //which will allow an engine to keep it moving. Zoom is in pixels/meter.
    //Safe to move or copy.
    class Camera
    {
    public:
        //p = position, v = velocity, z = zoom
        Camera(const Vector& p = {}, const Vector& v = {}, double z = 100) 
        : position_{ p }, velocity_{ v }, zoom_{ z } 
        {}
        
        Vector& position()   { return position_; }
        Vector& velocity()   { return velocity_; }
        double& zoom()       { return zoom_; }

        //Updates position based on veloctiy and time (t)
        void update(double t) 
        {
            position_ += velocity_ * t;
        }

    private:
        Vector position_;
        Vector velocity_;
        double zoom_;
    };
}