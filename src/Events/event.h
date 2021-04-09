#pragma once

#include "dispatcher.h"

namespace event
{
    class Event
    {
    public:
        //Initialize using dispatcher directly
        Event(void* d, Dispatcher& e_d) 
        : data_{ d }, dispatcher_{ &e_d } 
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