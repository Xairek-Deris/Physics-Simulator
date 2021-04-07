#pragma once

#include "event.h"

namespace phys
{
    struct Event_Handler
    {
        void (*handler)(void* handler_data, const void* event_data);
        void* data;
    };
}