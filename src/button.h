#pragma once

#include "element.h"
#include "Display/texture.h"
#include "Events/handler.h"
#include "Display/box.h"
#include "Display/point.h"


namespace sim
{
    class Button : public Element
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
            )
        :   clicked_{ false },
            hovered_{ false },
            on_click_{ on_click },
            on_press_{ press, this },
            on_release_{ release, this },
            Element({def_tex, click_tex, hover_tex, dis_tex}, box)
        {}

        void click()
        {
            on_click_.handle(NULL);
        }

        event::Handler& on_click()          { return on_click_; }
        const event::Handler& on_press()    { return on_press_; }
        const event::Handler& on_release()  { return on_release_; }

    private:
        bool clicked_;
        bool hovered_;
        event::Handler on_click_;
        event::Handler on_press_;
        event::Handler on_release_;

        static void press(void* d,  const void* e)
        {
            disp::Point point = *((disp::Point*)e);
            Button button = *((Button*)d);

            if(button.box().contains_point(point))
            {
                button.clicked_ = true;
            }
        }

        static void release(void* d,  const void* e)
        {
            Button button = *((Button*)d);
            disp::Point point = *((disp::Point*)e);

            if(button.clicked_ && button.box().contains_point(point))
            {
                button.clicked_ = true;
            }
            button.clicked_ = false;
        }
    };
}