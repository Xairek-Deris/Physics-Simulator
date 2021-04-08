#pragma once

#include <vector>

namespace event
{
        /*
        Handles a given event according to the function and data
        given to it. Create one of these for each action you want
        to trigger for a given event type. Needs to be registered 
        with a dispatcher to receive events, though you can call
        it directly with raw data using handle()
    */
    class Handler
    {
    public:
        //Creates unregistered handler
        Handler(void (*h)(void*, const void*), void* d)
        : handler_{ h }, data_{ d }, dispatcher_{ NULL }
        {}

        //Creates and registers handler with the dispatcher
        Handler(void (*h)(void*, const void*), void* d, Dispatcher& e_d)
        : handler_{ h }, data_{ d }
        {
            e_d.register_handler(*this);
        }

        //Creates registered handler. Requires the dispatcher to be initialized 
        //with this handler's address at the index provided or they will not connect
        Handler(void (*h)(void*, const void*), void* d, Dispatcher& e_d, unsigned i)
        : handler_{ h }, data_{ d }, dispatcher_{ &e_d }, index_{ i }
        {}

        //Updates address stored by the dispatcher with current address
        void update_registration()
        {
            dispatcher_->handlers_[index_] = this;
        }

        //Calls the handling function with the data given
        void handle(const void* d)
        {
            handler_(data_, d);
        }

        Dispatcher* dispatcher()
        {
            return dispatcher_;
        }

    private:
        void (*handler_)(void* misc_data, const void* event_data);
        void* data_;
        Dispatcher* dispatcher_;
        unsigned index_;
        friend class Dispatcher;
    };






    /*
        Dispatches events to registered handlers. Make one of these
        for each event type you want to be able to process
    */
    class Dispatcher
    {
    public:
        /*
            h = the event handler pointers to initialize with.
            Completes half the registration process, the other half
            is done by initializing the handlers with the constructor
            that takes an integer as one of the arguments
        */
        Dispatcher(const std::vector<Handler*>& h = {})
        : handlers_{ h }
        {}

        Dispatcher() {}

        //calls all registered handlers using the data provided
        void dispatch(const void* d)
        {
            for(auto h : handlers_)
            {
                h->handle(d);
            }
        }

        //registers handler with dispatcher so it will receive all events
        void register_handler(Handler& h)
        {
            unsigned index = handlers_.size();
            handlers_.push_back(&h);
            h.index_ = index;
        }

        //Removes handler from dispatcher and updates all
        //other registered handlers accordingly
        void unregister_handler(Handler& h)
        {
            handlers_.erase(handlers_.begin() + h.index_);
            for(auto j = h.index_; j < handlers_.size(); j++)
            {
                handlers_[j]->index_--;
            }
        }

        //Updates dispatcher address for all registered handlers
        void update_addresses()
        {
            for(auto h : handlers_)
                h->dispatcher_ = this;
        }

    private:
        std::vector<Handler*> handlers_;
        friend class Handler;
    };
}//namespace event