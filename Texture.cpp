#include "Texture.h"

#include <string>

#include <SDL2/SDL.h>

#include "Renderer.h"


disp::Texture::Texture(const std::string& filename, const Renderer& renderer)
{
    SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
    m_renderer = renderer.m_renderer;
    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);
}