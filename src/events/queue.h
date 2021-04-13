#pragma once

#include <mutex>
#include <queue>

#include "event.h"

namespace event
{
    //Thread-safe queue to store and dispatch events.
    class Queue
    {
    public:        
        //Push an event onto the queue
        void Push_Event(Event& e)
        {
            mutex_.lock();
            events_.push(e);
            mutex_.unlock();
        }

        //Dispatch the event at the front of the queue
        //Returns 0 if queue was empty, or 1 if success
        int dispatch_event();

        void lock()
        {
            mutex_.lock();
        }

        void unlock()
        {
            mutex_.unlock();
        }

    private:
        std::queue<Event> events_;
        std::mutex mutex_;
    };
} //namespace event