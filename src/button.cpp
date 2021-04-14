#include "button.h"

#include "display/display.h"

sim::Button::Button
(
    const disp::Texture& texture,
    const disp::Box& box,
    void (*on_click)(void*),
    void* data
)
:   pressed_{ false },
    hovered_{ false },
    disabled_{ false },
    shown_{ true },

    texture_{ texture },
    box_{ box },

    on_click_{ on_click },
    data_{ data }
{}

void sim::Button::press(const disp::Point& p)
{
    if(hovered_ && !disabled_)
    {
        pressed_ = true;
    }
}

void sim::Button::release(const disp::Point& p)
{
    if(pressed_ && hovered_)
    {
        on_click_(data_);
    }
    pressed_ = false;
}