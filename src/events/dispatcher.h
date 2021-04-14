#pragma once

#include <algorithm>

#include "handler.h"

namespace event
{
    /*
        Dispatches events to registered handlers. Make one of these
        for each event type you want to be able to process
    */
    class Dispatcher
    {
    public:
        Dispatcher() {}

        //Initializes dispatcher with handlers. Handlers will be registered.
        Dispatcher(const std::vector<Handler*>& h = {})
        : handlers_{ h }
        {}

        //Calls all registered handlers using the data provided
        void dispatch(const void* d)
        {
            for(auto h : handlers_)
            {
                h->handle(d);
            }
        }

        //Registers handler with dispatcher so it will receive all events
        void register_handler(Handler& h)
        {
            handlers_.push_back(&h);
        }

        //Removes handler from dispatcher, do this if you delete a handler.
        void unregister_handler(Handler& h)
        {
            handlers_.erase(find(handlers_.begin(), handlers_.end(), &h));
        }

    private:
        std::vector<Handler*> handlers_;
    };
}