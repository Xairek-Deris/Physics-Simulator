#pragma once

namespace phys
{
    struct Event
    {
        Event(void* d, unsigned i) : data{ d }, index{ i } {}
        
        void* data;
        unsigned index;
    };
}