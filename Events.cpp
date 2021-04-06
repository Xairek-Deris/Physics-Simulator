#include "Events.h"

#include <mutex>

int phys::Event_Loop::Function(void* e_loop)
{
    #define LOOP (*(Event_Loop*)e_loop)
    while(!LOOP.m_stop)
    {
        if(!LOOP.m_events.empty())
        {
            LOOP.m_mutex.lock();
            Event e = LOOP.m_events.front();
            LOOP.m_events.pop();
            LOOP.m_mutex.unlock();
            e.Handler(e.data);
        }
    }
    return 0;
}