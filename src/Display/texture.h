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
        Texture(const std::string& f, Renderer& r)
        : renderer_{ &r }
        {
            SDL_Surface* surface = SDL_LoadBMP(f.c_str());
	        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            texture_ = SDL_CreateTextureFromSurface(renderer_->renderer(), surface);
            SDL_FreeSurface(surface);
            ref_count_++;
        }

        Texture(const Texture& texture)
        : texture_{ texture.texture_ }, renderer_{ texture.renderer_ }
        {
            ref_count_++;
        }

        Texture(const Texture&& texture)
        : texture_{ texture.texture_ }, renderer_{ texture.renderer_ }
        {
            ref_count_++;
        }

        ~Texture()
        {
            if(--ref_count_ == 0)
                SDL_DestroyTexture(texture_);
        }

        void draw(const Box& box) const
        {
            SDL_RenderCopy(renderer_->renderer(), texture_, NULL, box.rect());
        }
        
        SDL_Texture* texture() { return texture_; }

    private:
        SDL_Texture* texture_;
        Renderer* renderer_;
        inline static int ref_count_;
    };
} //namespace disp