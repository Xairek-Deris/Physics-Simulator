#include "Window.h"

win::Window::Window(const char * title, int width, int height)
{
    if(!sdl_initialized)
    {
        if(SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return;
        }
        sdl_initialized = true;
    }

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if(m_window == NULL)
    {
       std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }
    
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}