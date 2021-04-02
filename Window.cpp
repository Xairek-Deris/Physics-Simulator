#include "Window.h"

#include <SDL2/SDL.h>

int phys::Window::Poll_Event()
{
    if(SDL_PollEvent(&m_event) != 0)
    {
        if(m_event.type == SDL_MOUSEMOTION || m_event.type == SDL_MOUSEBUTTONDOWN || m_event.type == SDL_MOUSEBUTTONUP)
        {
            m_mouse_state = SDL_GetMouseState(&m_mouse_x, &m_mouse_y);
        }
        else if(m_event.type == SDL_WINDOWEVENT)
        {
            if(m_event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                m_width = m_event.window.data1;
                m_height = m_event.window.data2;
            }
        }
        else if(m_event.type == SDL_QUIT)
            m_quit = true;
        return 1;
    }
    return 0;
}