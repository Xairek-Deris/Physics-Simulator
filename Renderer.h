#pragma once

#include <SDL2/SDL.h>

#include "Window.h"

namespace phys
{
    class Renderer
    {
    public:
        Renderer(const Window& window)
        {
            m_renderer = SDL_CreateRenderer(window.m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }

        void Clear() { SDL_RenderClear(m_renderer); }
        void Update() { SDL_RenderPresent(m_renderer); } 

    private:
        SDL_Renderer* m_renderer;
        friend class Texture;
    };
}