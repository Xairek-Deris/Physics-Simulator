#include <vector>

#include "Display/box.h"
#include "Display/texture.h"
#include "Events/event.h"
#include "Events/handler.h"

namespace sim
{
    //a combination of event handlers and textures to be drawn
    class Element
    {
    public:
        Element(const std::vector<disp::Texture>& t, 
                    const std::vector<event::Handler>& h, const disp::Box& b)
        : textures_{ t }, handlers_{ h }, box_{ b }, texture_{ 0 }
        {}

        void add_texture(const disp::Texture& t)
        {
            textures_.push_back(t);
        }

        void delete_texture(unsigned t)
        {
            textures_.erase(textures_.begin() + t);
        }

        //The box where the texture will be painted
        disp::Box& box()
        {
            return box_;
        }

        //The index of the texture to be painted
        unsigned& active_texture()
        {
            return texture_;
        }

        //paints the active texture onto the screen
        void paint()
        {
            textures_[texture_].draw(box_);
        }

        //updates the registrations for all handlers
        void update_registrations()
        {
            for(auto h : handlers_)
                h.update_registration();
        }

    private:
        std::vector<disp::Texture> textures_;
        std::vector<event::Handler> handlers_;
        disp::Box box_;
        unsigned texture_;
    };
} //namespace sim