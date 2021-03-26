#include "Window.h"

#include <iostream>

#include <SDL2/SDL.h>

void disp::Window::Poll_Events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
    if(event.type == SDL_QUIT)
        {
            m_quit = true;
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
}