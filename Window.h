#pragma once

#include <string>

#include <SDL2/SDL.h>

namespace phys
{
    class Window
    {
    public:
        Window(const std::string& title, int width, int height)
        : m_width{ width }, m_height{ height }, m_quit { false }
        {
            m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            m_keystates = SDL_GetKeyboardState( NULL );
            m_mouse_state = SDL_GetMouseState(&m_mouse_x, &m_mouse_y);
        }

        void Free(){ SDL_DestroyWindow(m_window); }
        int Poll_Event();
        int Width() const { return m_width; }
        int Height() const { return m_height; }
        int Mouse_X() const { return m_mouse_x; }
        int Mouse_Y() const { return m_mouse_y; }
        bool Button_Is_Pressed(int scancode) { return m_keystates[scancode]; }
        bool MB_Is_Pressed(int button) { return m_mouse_state & SDL_BUTTON(button); }
        bool Should_Quit() { return m_quit; }
        const SDL_Event& Event() { return m_event; }
        SDL_Window* Get_Window() { return m_window; }

    private:
        int m_width, m_height;
        int m_mouse_x, m_mouse_y;
        bool m_quit;
        SDL_Window* m_window;
        const Uint8* m_keystates;
        Uint32 m_mouse_state;
        SDL_Event m_event;
        friend class Display;
    };
}