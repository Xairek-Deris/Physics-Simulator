#include "button.h"

#include "display/display.h"

sim::Button::Button
(
    const disp::Texture& text_tex,
    const disp::Box& box,
    void (*on_click)(void*),
    void* data
)
:   pressed_{ false },
    hovered_{ false },
    disabled_{ false },
    shown_{ true },

    text_tex_{ text_tex },
    active_tex_{ &default_tex_ },
    box_{ box },

    on_click_{ on_click },
    data_{ data }
{}

void sim::Button::press(disp::Point& p)
{
    if(hovered_ && !disabled_)
    {
        active_tex_ = &pressed_tex_;
        pressed_ = true;
    }
}

void sim::Button::release(disp::Point& p)
{
    active_tex_ = &default_tex_;
    if(pressed_ && hovered_)
    {
        on_click_(data_);
    }
    pressed_ = false;
}

void sim::Button::hover(disp::Point& p)
{
    if(!disabled_)
    {
        if(box_.contains_point(p))
        {
            hovered_ = true;
            active_tex_ = &hover_tex_;
        }
        else
        {
            hovered_ = false;
            active_tex_ = &default_tex_;
        }
    }
}

void sim::Button::enable()
{
    disabled_ = false;
    active_tex_ = &default_tex_;
}

void sim::Button::disable()
{
    disabled_ = true;
    active_tex_ = &disabled_tex_;
}

void sim::Button::load_textures(disp::Renderer& r)
{
    default_tex_    = disp::Texture("../res/button_default.bmp", r);
    pressed_tex_    = disp::Texture("../res/button_pressed.bmp", r);
    hover_tex_      = disp::Texture("../res/button_hover.bmp", r);
    disabled_tex_   = disp::Texture("../res/button_disabled.bmp", r);
}

disp::Texture default_tex_;
disp::Texture pressed_tex_;
disp::Texture hover_tex_;
disp::Texture disabled_tex_;