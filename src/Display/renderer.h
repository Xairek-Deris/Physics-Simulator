#pragma once

#include <SDL2/SDL.h>

#include "window.h"

namespace disp
{
    //Renderer class for drawing textures onto a window. Safe to move or copy.
    class Renderer
    {
    public:
        Renderer(Window& window)
        : window_{ &window }
        {
            renderer_ = SDL_CreateRenderer(window_->window(), -1, 
                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
            ref_count_++;
        }

        Renderer(const Renderer& renderer)
        : window_{ renderer.window_ }, renderer_{ renderer.renderer_ }
        {
            ref_count_++;
        }

        Renderer(const Renderer&& renderer)
        : window_{ renderer.window_ }, renderer_{ renderer.renderer_ }
        {
            ref_count_++;
        }

        ~Renderer() { if(--ref_count_ == 0) SDL_DestroyRenderer(renderer_); }
        
        //Wipes screen and paints it white
        void clear() { SDL_RenderClear(renderer_); }

        //Updates the screen anything drawn since last update
        void display() { SDL_RenderPresent(renderer_); }

        SDL_Renderer* renderer() { return renderer_; }

    private:
        Window* window_;
        SDL_Renderer* renderer_;
        inline static int ref_count_;
    };
} //namespace disp