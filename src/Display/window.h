#pragma once

#include <string>

#include <SDL2/SDL.h>

namespace disp
{
    //Window class that creates window upon construction. Safe to move or copy.
    class Window
    {
    public:
        Window(const std::string& title, int width, int height)
        : width_{ width }, height_{ height }, quit_ { false }
        {
            window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height, 
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

            keystates_ = SDL_GetKeyboardState( NULL );
            mouse_state_ = SDL_GetMouseState(&mouse_x_, &mouse_y_);
            ref_count_++;
        }

        Window(const Window& w)
        : width_{ w.width_ }, height_{ w.height_ }, 
            mouse_x_{ w.mouse_x_ }, mouse_y_{ w.mouse_y_ }, quit_ { false }, 
            window_{ w.window_ }, keystates_{ w.keystates_ }, 
            mouse_state_{ w.mouse_state_ }, event_{ w.event_ }
        {
            ref_count_++;
        }

        Window(const Window&& w)
        : width_{ w.width_ }, height_{ w.height_ }, mouse_x_{ w.mouse_x_ }, 
            mouse_y_{ w.mouse_y_ }, quit_ { false }, window_{ w.window_ }, 
            keystates_{ w.keystates_ }, mouse_state_{ w.mouse_state_ }, 
            event_{ w.event_ }
        {
            ref_count_++;
        }

        ~Window() { if(--ref_count_ == 0) SDL_DestroyWindow(window_); }

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
        
        inline static int ref_count_;

        friend class Display;
    };
} //namespace disp

//TODO encapsulate SDL enums