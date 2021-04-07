#include "window.h"

#include <SDL2/SDL.h>

int disp::Window::poll_event()
{
    if(SDL_PollEvent(&event_) != 0)
    {
        if(    event_.type == SDL_MOUSEMOTION 
            || event_.type == SDL_MOUSEBUTTONDOWN 
            || event_.type == SDL_MOUSEBUTTONUP)
        {
            mouse_state_ = SDL_GetMouseState(&mouse_x_, &mouse_y_);
        }

        else if(event_.type == SDL_WINDOWEVENT)
        {
            if(event_.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                width_  = event_.window.data1;
                height_ = event_.window.data2;
            }
        }

        else if(event_.type == SDL_QUIT)
            quit_ = true;

        return 1;
    }
    return 0;
}