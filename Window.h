#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>

namespace disp
{
    class Window
    {
    public:
        Window(const std::string& title, int width, int height)
        : m_width{ width }, m_height{ height }, m_window{ NULL }, m_close{ false }
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
        bool Should_Close() { return m_close; }
        void Close() { m_close = true; }

    private:
        int m_width;
        int m_height;
        bool m_close;
        SDL_Window* m_window;
        friend class Renderer;
    };
}