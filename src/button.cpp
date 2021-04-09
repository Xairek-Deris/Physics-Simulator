#include "button.h"

#include "Display/box.h"
#include "Display/point.h"
#include "Display/texture.h"
#include "Events/handler.h"

sim::Button::Button
(
    const event::Handler& on_click,
    const disp::Texture& def_tex,
    const disp::Texture& click_tex,
    const disp::Texture& hover_tex,
    const disp::Texture& dis_tex,
    const disp::Box& box
)
:   clicked_{ false },
    hovered_{ false },
    disabled_{ false },
    shown_{ true },

    on_click_{ on_click },
    on_press_{ press, this },
    on_release_{ release, this },
    on_mouse_move_{ move, this },

    default_tex_{ def_tex} ,
    click_tex_{ click_tex },
    hover_tex_{ hover_tex },
    disabled_tex_{ dis_tex },

    active_tex_{ &default_tex_ },

    box_{ box }
{}

void sim::Button::move(void* d,  const void* e)
{
    Button button = *((Button*)d);
    disp::Point point = *((disp::Point*)e);

    if(!button.hovered_ 
       && !button.disabled_ 
       && button.box_.contains_point(point))
    {
        button.hovered_ = true;
        button.active_tex_ = &button.hover_tex_;
    }

    else if(button.hovered_)
    {
        button.hovered_ = false;
        button.active_tex_ = &button.default_tex_;
    }
}

void sim::Button::press(void* d,  const void* e)
{
    Button button = *((Button*)d);

    if(!button.disabled_ && button.hovered_)
    {
        button.clicked_ = true;
        button.active_tex_ = &button.click_tex_;
    }
}

void sim::Button::release(void* d,  const void* e)
{
    Button button = *((Button*)d);

    if(button.clicked_ && button.hovered_)
    {
        button.clicked_ = true;
    }
    button.clicked_ = false;
}