#pragma once

#include <iostream>

#include <SDL2/SDL.h>

namespace win
{
    class Window
    {
    public:
        Window(const char * title, int width, int height);

        ~Window()
        {
            SDL_DestroyWindow(m_window);
            SDL_DestroyRenderer(m_renderer);
        }

        bool should_close;

        void Update();
        void Clear() { SDL_RenderClear(m_renderer); }
        int Height() { return m_height; }
        int Width() { return m_width; }
        static int Init()
        {
            if(SDL_Init(SDL_INIT_VIDEO) != 0)
            {
                std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
                return -1;
            }
            return 0;
        }

    private:
        int m_width;
        int m_height;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        friend class Texture;
    };
}