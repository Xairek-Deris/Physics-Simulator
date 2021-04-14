#pragma once

#include "display/display.h"


namespace sim
{
    class Button
    {
    public:
        Button
        (
            const disp::Texture& text_tex,
            const disp::Box& box,
            void (*on_click)(void*),
            void* data
        );

        void draw()
        {
            if(shown_)
            {
                active_tex_->draw(box_);
                text_tex_.draw(box_);
            }
        }

        void press(disp::Point& p);
        void release(disp::Point& p);
        void hover(disp::Point& p);
        void enable();
        void disable();
        void show() { shown_ = true; }
        void hide() { shown_ = false; }

    private:
        bool pressed_;
        bool hovered_;
        bool disabled_;
        bool shown_;

        disp::Texture text_tex_;
        disp::Texture* active_tex_;
        disp::Box box_;

        void (*on_click_)(void* data);
        void* data_;

        static void load_textures(disp::Renderer& r);

        static disp::Texture default_tex_;
        static disp::Texture pressed_tex_;
        static disp::Texture hover_tex_;
        static disp::Texture disabled_tex_;
    };
} //namespace sim