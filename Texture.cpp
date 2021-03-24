#include "Texture.h"
#include "Window.h"

win::Texture::Texture(const char* file, Window* window)
{
    SDL_Surface* surface = SDL_LoadBMP(file);
    m_texture = SDL_CreateTextureFromSurface(window->m_renderer, surface);
    m_renderer = window->m_renderer;
    SDL_FreeSurface(surface);
}

void win::Texture::Draw(int x, int y, int width, int height)
{
    SDL_Rect rect {x, y, width, height};
    SDL_RenderCopy(m_renderer, m_texture, NULL, &rect);
}