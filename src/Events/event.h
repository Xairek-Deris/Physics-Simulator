#pragma once

#include "event_handler.h"

namespace event
{
    class Event
    {
    public:
        //Initialize using dispatcher directly
        Event(void* d, EventDispatcher& e_d) 
        : data_{ d }, dispatcher_{ &e_d } 
        {}

        //Initialize even using dispatcher from a handler
        Event(void* d, EventHandler& e_h) 
        : data_{ d }, dispatcher_{ e_h.dispatcher() } 
        {}

        void process()
        {
            dispatcher_->dispatch(data_);
        }

    private:
        void* data_;
        EventDispatcher* dispatcher_;
    };
} //namespace event