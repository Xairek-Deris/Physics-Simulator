#pragma once

#include <mutex>
#include <queue>

#include <SDL2/SDL_thread.h>

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
        Event_Loop() : m_stop{ false }, m_thread{ NULL } {}

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
            m_thread = SDL_CreateThread(Function, "Event Loop Thread", this);
        }

        void Stop() 
        { 
            m_stop = true;
            SDL_WaitThread(m_thread, NULL);
        }

    private:
        std::queue<Event> m_events;
        std::mutex m_mutex;
        SDL_Thread* m_thread;
        bool m_stop;

        static int Function(void* e_loop);
    };
}