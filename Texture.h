#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "Window.h"

namespace win
{
    class Texture
    {
    public:
        Texture(const std::string& filename, const Window& window);
        ~Texture() { SDL_DestroyTexture(m_texture); }
        void Draw(int x, int y, int w, int h) const
        {
            SDL_Rect rect {x, y, w, h};
            SDL_RenderCopy(m_renderer, m_texture, NULL, &rect);
        }

    private:
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;
    };
}