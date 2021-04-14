#pragma once

#include <string>

#include <SDL2/SDL.h>

namespace disp
{
    //Window class that creates window upon construction. Safe to move or copy.
    class Window
    {
    public:
        Window(const std::string& title, int width, int height);
        Window(const Window& w);
        Window(const Window&& w);
        ~Window();

        int width()     const { return width_; }
        int height()    const { return height_; }
        int mouse_x()   const { return mouse_x_; }
        int mouse_y()   const { return mouse_y_; }

        SDL_Window* window()        { return window_; }
        const SDL_Event& event()    { return event_; }
        bool should_quit()          { return quit_; }

        bool button_is_pressed(int scancode)    { return keystates_[scancode]; }
        bool mb_is_pressed(int button)          { return mouse_state_ & SDL_BUTTON(button); }

        //Get next SDL event. Must be called to update key and mouse states
        int poll_event();

    private:
        int width_;
        int height_;
        int mouse_x_;
        int mouse_y_;
        bool quit_;

        SDL_Window* window_;
        SDL_Event event_;

        const Uint8* keystates_;
        Uint32 mouse_state_;
        
        static int ref_count_;
    };
} //namespace disp

//TODO encapsulate SDL enums