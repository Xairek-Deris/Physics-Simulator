#include "event_loop.h"

int phys::Event_Loop::Function(void* e_l)
{
    #define LOOP (*(Event_Loop*)e_l)
    while(!LOOP.m_stop)
    {
        if(!LOOP.m_events.empty())
        {
            LOOP.m_mutex.lock();
            Event e = LOOP.m_events.front();
            LOOP.m_events.pop();
            LOOP.m_mutex.unlock();
            for(auto i : LOOP.m_registry[e.index])
            {
                LOOP.m_event_handlers[i].handler(LOOP.m_event_handlers[i].data, e.data);
            }
        }
    }
    return 0;
}