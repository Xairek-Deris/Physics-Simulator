#pragma once

#include <SDL2/SDL.h>

#include "Window.h"

namespace phys
{
    class Renderer
    {
    public:
        Renderer(Window& window)
        : m_window{ &window }
        {
            m_renderer = SDL_CreateRenderer(m_window->Get_Window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
        void Free() { SDL_DestroyRenderer(m_renderer); }

        void Clear() { SDL_RenderClear(m_renderer); }
        void Display() { SDL_RenderPresent(m_renderer); }
        SDL_Renderer* Get_Renderer() { return m_renderer; }

    private:
        Window* m_window;
        SDL_Renderer* m_renderer;
    };
}