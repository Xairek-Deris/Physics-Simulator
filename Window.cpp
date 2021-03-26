#include "Window.h"

#include <iostream>

#include <SDL2/SDL.h>

win::Window::Window(const char * title, int width, int height)
    : m_width{ width }, m_height{ height }, m_window{ NULL }, m_renderer{ NULL }, should_close{ false }
{
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(m_window == NULL)
    {
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void win::Window::Update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
    if(event.type == SDL_QUIT)
        {
            should_close = true;
        }
        else if ( event.type == SDL_WINDOWEVENT )
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                m_width = event.window.data1;
                m_height = event.window.data2;
            }
        }
    }
    SDL_RenderPresent(m_renderer); 
}