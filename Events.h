#pragma once

#include <mutex>
#include <queue>

#include "Thread.h"

namespace phys
{
    struct Event
    {
        void (*Handler)(void*);
        void* data;
    };

    class Event_Loop
    {
    public:
        Event_Loop() : m_stop{ false }, m_thread{ "Event Loop Thread" } {}

        ~Event_Loop() { if(!m_stop) Stop(); }

        void Push(void (*handler)(void*), void* data)
        {
            m_mutex.lock();
            m_events.push({ handler, data });
            m_mutex.unlock();
        }

        void Start()
        {
            m_stop = false;
            m_thread.Start(Function, this);
        }

        void Stop() 
        { 
            m_stop = true;
            m_thread.Wait();
        }

    private:
        std::queue<Event> m_events;
        std::mutex m_mutex;
        phys::Thread m_thread;
        bool m_stop;

        static int Function(void* e_loop);
    };
}