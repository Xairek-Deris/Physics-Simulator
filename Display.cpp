#include "Display.h"

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "Window.h"

namespace phys{ extern long long dframes; }

phys::Display::Display(Window& window,  const Space& space, const std::string& texture_filename)
: m_thread{ NULL }, m_window{ &window }, m_space{ &space }, m_camera{ 0, 0, 0 }, m_zoom{ 100 }, m_stop{ false }
{
    m_surface = SDL_LoadBMP(texture_filename.c_str());
    SDL_SetColorKey(m_surface, SDL_TRUE, SDL_MapRGB( m_surface->format, 0xFF, 0xFF, 0xFF ) );
}

void phys::Display::Start()
{
    m_stop = false;
    m_thread = SDL_CreateThread(Function, "Display Thread", (void*)this);
}

void phys::Display::Stop()
{
    m_stop = true;
    int ret;
    SDL_WaitThread(m_thread, &ret);
}

int phys::Display::Function(void* display)
{
    #define DISPLAY ((Display*)display)
    SDL_Renderer* renderer = SDL_CreateRenderer(DISPLAY->m_window->Get_Window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, DISPLAY->m_surface);
    while(!DISPLAY->m_stop)
    {
        SDL_Rect rect;
        SDL_RenderClear(renderer);
        for(auto& i : DISPLAY->m_space->particles)
        {
            rect.x = (i.position.x - DISPLAY->m_camera.x - i.radius) * DISPLAY->m_zoom + DISPLAY->m_window->Width() / 2;
            rect.y = DISPLAY->m_window->Height() / 2 - (i.position.y - DISPLAY->m_camera.y + i.radius) * DISPLAY->m_zoom;
            rect.w = i.radius * 2 * DISPLAY->m_zoom;
            rect.h = i.radius * 2 * DISPLAY->m_zoom;
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }
        for(auto& i : DISPLAY->m_space->obstacles)
        {
            rect.x = (i.position.x - DISPLAY->m_camera.x - i.radius) * DISPLAY->m_zoom + DISPLAY->m_window->Width() / 2;
            rect.y = DISPLAY->m_window->Height() / 2 - (i.position.y - DISPLAY->m_camera.y + i.radius) * DISPLAY->m_zoom;
            rect.w = i.radius * 2 * DISPLAY->m_zoom;
            rect.h = i.radius * 2 * DISPLAY->m_zoom;
            SDL_RenderCopy(renderer, texture, NULL, &rect);
        }
        SDL_RenderPresent(renderer);
        dframes++;
    }
    return 0;
}