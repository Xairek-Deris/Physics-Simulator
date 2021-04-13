#pragma once

#include <SDL2/SDL.h>

#include "window.h"

namespace disp
{
    //Renderer class for drawing textures onto a window. Safe to move or copy.
    class Renderer
    {
    public:
        Renderer(Window& window);
        Renderer(const Renderer& renderer);
        Renderer(const Renderer&& renderer);
        ~Renderer();
        
        //Wipes screen and paints it white
        void clear() { SDL_RenderClear(renderer_); }

        //Updates the screen anything drawn since last update
        void display() { SDL_RenderPresent(renderer_); }

        SDL_Renderer* renderer() { return renderer_; }

    private:
        Window* window_;
        SDL_Renderer* renderer_;
        static int ref_count_;
    };
} //namespace disp