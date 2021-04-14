#pragma once

#include <vector>

namespace event
{
    /*
        Base class for any handler. Needs to be registered with a dispatcher 
        to receive events. Child classes must be created to handle events, 
        as the base class uses a pure virtual function.
    */
    class Handler
    {
    public:
        //Calls the handling function with the data given
        virtual void handle(const void* d) = 0;
    };
}//namespace event