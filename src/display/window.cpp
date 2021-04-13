#include "window.h"

#include <SDL2/SDL.h>

int disp::Window::ref_count_{ 0 };

disp::Window::Window(const std::string& title, int width, int height)
: width_{ width }, height_{ height }, quit_ { false }
{
    window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED, width, height, 
                    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    keystates_ = SDL_GetKeyboardState( NULL );
    mouse_state_ = SDL_GetMouseState(&mouse_x_, &mouse_y_);
    ref_count_++;
}

disp::Window::Window(const Window& w)
: width_{ w.width_ }, height_{ w.height_ }, 
    mouse_x_{ w.mouse_x_ }, mouse_y_{ w.mouse_y_ }, quit_ { false }, 
    window_{ w.window_ }, keystates_{ w.keystates_ }, 
    mouse_state_{ w.mouse_state_ }, event_{ w.event_ }
{
    ref_count_++;
}

disp::Window::Window(const Window&& w)
: width_{ w.width_ }, height_{ w.height_ }, mouse_x_{ w.mouse_x_ }, 
    mouse_y_{ w.mouse_y_ }, quit_ { false }, window_{ w.window_ }, 
    keystates_{ w.keystates_ }, mouse_state_{ w.mouse_state_ }, 
    event_{ w.event_ }
{
    ref_count_++;
}

disp::Window::~Window()
{
    if(--ref_count_ == 0)
        SDL_DestroyWindow(window_);
}

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