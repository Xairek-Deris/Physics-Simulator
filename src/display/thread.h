#pragma once

#include <string>

#include <SDL2/SDL_thread.h>

namespace disp
{   
    
    //Thread handle that can be used to create and wait for threads
    class Thread
    {
    public:
        Thread() 
        : thread_{ NULL } 
        {}

        void start(int (*f)(void*), const std::string& n, void* d)
        {
            thread_ = SDL_CreateThread(f, n.c_str(), d);
        }

        //Waits for thread to end, does not kill the thread.
        int wait()
        {
            int ret;
            SDL_WaitThread(thread_, &ret);
            return ret;
        }

    private:
        SDL_Thread* thread_;
    };
} //namespace disp