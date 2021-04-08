#pragma once

#include "handler.h"

namespace event
{
    class Event
    {
    public:
        //Initialize using dispatcher directly
        Event(void* d, Dispatcher& e_d) 
        : data_{ d }, dispatcher_{ &e_d } 
        {}

        //Initialize even using dispatcher from a handler
        Event(void* d, Handler& e_h) 
        : data_{ d }, dispatcher_{ e_h.dispatcher() } 
        {}

        void process()
        {
            dispatcher_->dispatch(data_);
        }

    private:
        void* data_;
        Dispatcher* dispatcher_;
    };
} //namespace event