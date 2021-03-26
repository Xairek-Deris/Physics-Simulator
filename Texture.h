#pragma once

#include <SDL2/SDL.h>

#include "Window.h"

namespace win
{
    class Texture
    {
    public:
        Texture(const char* file, Window& window);
        ~Texture() { SDL_DestroyTexture(m_texture); }
        void Draw(int x, int y, int width, int height)
        {
            SDL_Rect rect {x, y, width, height};
            SDL_RenderCopy(m_renderer, m_texture, NULL, &rect);
        }

    private:
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;
    };
}