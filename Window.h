#pragma once

#include <string>

#include <SDL2/SDL.h>

namespace phys
{
    class Window
    {
    public:
        Window(const std::string& title, int width, int height)
        : m_width{ width }, m_height{ height }, m_window{ NULL }, m_quit{ false }
        {
            m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        }

        ~Window()
        {
            SDL_DestroyWindow(m_window);
        }

        void Poll_Events();
        int Height() const { return m_height; }
        int Width() const { return m_width; }
        bool Should_Quit() { return m_quit; }
        void Quit() { m_quit = true; }
        SDL_Window* Get_Window() { return m_window; }

    private:
        int m_width;
        int m_height;
        bool m_quit;
        SDL_Window* m_window;
    };
}