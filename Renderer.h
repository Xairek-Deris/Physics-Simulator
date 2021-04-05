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
            m_ref_count++;
        }

        Renderer(const Renderer& renderer)
        : m_window{ renderer.m_window }, m_renderer{ renderer.m_renderer }
        {
            m_ref_count++;
        }

        Renderer(const Renderer&& renderer)
        : m_window{ renderer.m_window }, m_renderer{ renderer.m_renderer }
        {
            m_ref_count++;
        }

        ~Renderer() { if(--m_ref_count == 0) SDL_DestroyRenderer(m_renderer); }
        
        void Clear() { SDL_RenderClear(m_renderer); }
        void Display() { SDL_RenderPresent(m_renderer); }
        SDL_Renderer* Get_Renderer() { return m_renderer; }

    private:
        Window* m_window;
        SDL_Renderer* m_renderer;
        inline static int m_ref_count;
    };
}