#pragma once

#include <mutex>
#include <queue>
#include <vector>

#include "event.h"
#include "event_handler.h"

namespace phys
{
    class Event_Loop
    {
    public:
        Event_Loop(const std::vector<std::vector<unsigned>>& registry, const std::vector<Event_Handler>& event_handlers)
        : m_registry{ registry }, m_event_handlers{ event_handlers }, m_stop{ false } {}

        ~Event_Loop()
        {
            if(!m_stop)
                Stop();
        }
        
        void Push_Event(const Event& e)
        {
            m_mutex.lock();
            m_events.push(e);
            m_mutex.unlock();
        }
        void Start()
        {
            m_stop = false;
        }
        void Stop()
        {
            m_stop = true;
        }
        void Update_Data(unsigned i, void* d)
        {
            m_event_handlers[i].data = d;
        }
        void Update_Handler(unsigned i, void (*h)(void*, const void*))
        {
            m_event_handlers[i].handler = h;
        }
        int Register_Handler(const Event_Handler& h, unsigned t)
        {
            unsigned i = m_event_handlers.size();
            m_event_handlers.push_back(h);
            m_registry[t].push_back(i);
            return i;
        }

    private:
        std::vector<std::vector<unsigned>> m_registry;
        std::vector<Event_Handler> m_event_handlers;
        std::queue<Event> m_events;
        std::mutex m_mutex;
        bool m_stop;

        static int Function(void* e_l);
    };
}