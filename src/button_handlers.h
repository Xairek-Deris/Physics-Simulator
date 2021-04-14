#pragma once

#include "button.h"
#include "display/display.h"
#include "events/events.h"

namespace sim
{
    class Button_MB1_Down: public event::Handler
    {
    public:
        Button_MB1_Down(Button& button)
        : button_{ &button }
        {}

        void handle(const void* data) override
        {
            button_->press(*((const disp::Point*) data));
        }

    private:
        Button* button_;
    };

    class Button_MB1_Up: public event::Handler
    {
    public:
        Button_MB1_Up(Button& button)
        : button_{ &button }
        {}

        void handle(const void* data) override
        {
            button_->press(*((const disp::Point*) data));
        }

    private:
        Button* button_;
    };

    class Button_Mouse_Move: public event::Handler
    {
    public:
        Button_Mouse_Move(Button& button)
        : button_{ &button }
        {}

        void handle(const void* data) override
        {
            button_->press(*((const disp::Point*) data));
        }

    private:
        Button* button_;
    };

    class Button_Toggle_Vis: public event::Handler
    {
    public:
        Button_Toggle_Vis(Button& button)
        : button_{ &button }
        {}

        void handle(const void* data) override
        {
            static bool shown = true;
            if(shown)
            {
                button_->hide();
                button_->disable();
            }
            else
            {
                button_->show();
                button_->enable();
            }
            shown = !shown;
        }

    private:
        Button* button_;
    };
} //namespace sim