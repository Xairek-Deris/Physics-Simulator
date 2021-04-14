#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "box.h"
#include "renderer.h"

namespace disp
{
    //Texture class that loads bmp file from device into a useable format. Safe to move or copy.
    class Texture
    {
    public:
        Texture()
        : texture_{ NULL }, renderer_{ NULL }
        {}

        Texture(const std::string& f, Renderer& r);
        Texture(const Texture& texture);
        Texture(const Texture&& texture);
        ~Texture();

        Texture operator=(Texture& t);
        Texture operator=(Texture&& t);

        void draw(const Box& box) const
        {
            SDL_RenderCopy(renderer_->renderer(), texture_, NULL, box.rect());
        }
        
        SDL_Texture* texture() { return texture_; }

    private:
        SDL_Texture* texture_;
        Renderer* renderer_;
        static int ref_count_;
    };
} //namespace disp