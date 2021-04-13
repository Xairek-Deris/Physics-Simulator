#pragma once

#include <vector>

namespace event
{
    /*
        Handles a given event according to the function and data
        given to it. Create one of these for each action you want
        to trigger for a given event type. Needs to be registered 
        with a dispatcher to receive events, though you can call
        it directly with raw data using handle(). Safe to move 
        or copy, but will invalidate any registrations.
    */
    class Handler
    {
    public:
        Handler(void (*h)(void*, const void*), void* d)
        : handler_{ h }, data_{ d }
        {}

        //Calls the handling function with the data given
        void handle(const void* d)
        {
            handler_(data_, d);
        }

        bool operator==(const Handler& h)
        {
            return handler_ == h.handler_ && data_ == h.data_;
        }
        
    private:
        void (*handler_)(void* misc_data, const void* event_data);
        void* data_;
    };
}//namespace event