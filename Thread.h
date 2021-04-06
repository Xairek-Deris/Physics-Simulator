#pragma once

#include <string>

#include <SDL2/SDL_thread.h>

namespace phys
{
    class Thread
    {
    public:
        Thread(const std::string& name) : m_thread{ NULL }, m_name{ name } {} 

        void Start(int (*function)(void* data), void* data)
        {
            m_thread = SDL_CreateThread(function, m_name.c_str(), data);
        }

        void Wait()
        {
            SDL_WaitThread(m_thread, NULL);
        }

    private:
        SDL_Thread* m_thread;
        std::string m_name;
    };
}