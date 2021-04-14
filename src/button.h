#pragma once

#include "display/display.h"


namespace sim
{
    //Must call load textures successfully before use
    class Button
    {
    public:
        Button
        (
            const disp::Texture& texture,
            const disp::Box& box,
            void (*on_click)(void*),
            void* data
        );

        void draw()
        {
            if(shown_)
            {
                texture_.draw(box_);
            }
        }

        void press(const disp::Point& p);
        void release(const disp::Point& p);
        void hover(const disp::Point& p);

        void enable()   { disabled_ = false; }
        void disable()  { disabled_ = true; }
        void show()     { shown_ = true; }
        void hide()     { shown_ = false; }

    private:
        bool pressed_;
        bool hovered_;
        bool disabled_;
        bool shown_;

        disp::Texture texture_;
        disp::Box box_;

        void (*on_click_)(void* data);
        void* data_;
    };
} //namespace sim