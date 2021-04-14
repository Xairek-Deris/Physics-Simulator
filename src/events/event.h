#pragma once

#include "dispatcher.h"

namespace event
{
    class Event
    {
    public:
        //Initialize using dispatcher directly
        Event(void* data, Dispatcher& disp) 
        : data_{ data }, dispatcher_{ &disp } 
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