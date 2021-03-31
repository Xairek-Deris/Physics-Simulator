#include "Display.h"

#include <string>

#include <SDL2/SDL.h>

#include "Space.h"
#include "Window.h"

int phys::Display::New_Texture(const std::string& filename)
{
    size_t insert = textures.size();
    for(size_t i = 0; i < textures.size(); i++)
    {
        if(textures[i].second == filename)
            return i;
        if(textures[i].second == "")
            insert = i;
    }

    SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
    if(surface == NULL)
        return -1;
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    if(insert == textures.size())
        textures.push_back(std::pair<SDL_Texture*, std::string>(SDL_CreateTextureFromSurface(m_renderer, surface), filename));
    else 
    {
        textures[insert].first = SDL_CreateTextureFromSurface(m_renderer, surface);
        textures[insert].second = filename;
    }
    return insert;
}

void phys::Display::Draw_Particles(const std::vector<Particle>& particles, const Camera& camera)
{
        SDL_Rect rect;
        for(auto& i : particles)
        {
            rect.x = (i.position.x - camera.position.x - i.radius) * camera.zoom + m_window->Width() / 2;
            rect.y = m_window->Height() / 2 - (i.position.y - camera.position.y + i.radius) * camera.zoom;
            rect.w = i.radius * 2 * camera.zoom;
            rect.h = i.radius * 2 * camera.zoom;
            SDL_RenderCopy(m_renderer, textures[i.texture].first, NULL, &rect);
        }
}