#pragma once

#include <string>

#include <SDL2/SDL_thread.h>

namespace win
{
    class Thread
    {
    public:
        //Requires a function returning int that takes a void *
        Thread( int (*func)(void*), const std::string& name, void* arg)
        {
            m_thread = SDL_CreateThread(func, name.c_str(), arg);
        }
        int Wait() const
        {
            int ret;
            SDL_WaitThread(m_thread, &ret);
            return ret;
        }
    private:
        SDL_Thread* m_thread;
    };
}