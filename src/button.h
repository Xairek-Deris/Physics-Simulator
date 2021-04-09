#pragma once

#include "Display/box.h"
#include "Display/point.h"
#include "Display/texture.h"
#include "Events/handler.h"


namespace sim
{
    class Button
    {
    public:
        Button
        (
            const event::Handler& on_click,
            const disp::Texture& def_tex,
            const disp::Texture& click_tex,
            const disp::Texture& hover_tex,
            const disp::Texture& dis_tex,
            const disp::Box& box
        );

        void click()
        {
            on_click_.handle(NULL);
        }

        void paint()
        {
            if(shown_)
                active_tex_->draw(box_);
        }

        void enable()
        {
            disabled_ = false;
            active_tex_ = &default_tex_;
        }

        void disable()
        {
            disabled_ = true;
            active_tex_ = &disabled_tex_;
        }

        void show() { shown_ = true; }
        void hide() { shown_ = false; }

        event::Handler& on_click()      { return on_click_; }
        event::Handler& on_move()       { return on_mouse_move_; }
        event::Handler& on_press()      { return on_press_; }
        event::Handler& on_release()    { return on_release_; }

    private:
        bool clicked_;
        bool hovered_;
        bool disabled_;
        bool shown_;

        event::Handler on_click_;
        event::Handler on_mouse_move_;
        event::Handler on_press_;
        event::Handler on_release_;

        disp::Texture default_tex_;
        disp::Texture click_tex_;
        disp::Texture hover_tex_;
        disp::Texture disabled_tex_;

        disp::Texture* active_tex_;

        disp::Box box_;

        static void move(void* d,  const void* e);
        static void press(void* d,  const void* e);
        static void release(void* d,  const void* e);
    };
}