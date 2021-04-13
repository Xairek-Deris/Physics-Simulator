#include "queue.h"

int event::Queue::dispatch_event()
{
    if(events_.size() == 0)
        return 0;
    mutex_.lock();
    Event e = events_.front();
    events_.pop();
    mutex_.unlock();
    e.process();
    return 1;
}