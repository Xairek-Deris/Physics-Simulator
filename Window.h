#include <SDL2/SDL.h>
#include <iostream>
namespace win
{
    static bool sdl_initialized = false;

    class Window
    {
    public:
        Window(const char * title, int width, int height);

        ~Window()
        {
            SDL_DestroyWindow(m_window);
        }

        bool should_close;

        void Update();
        void Clear() { SDL_RenderClear(m_renderer); }
        int Height() {return m_height;}
        int Width() {return m_width;}
        SDL_Renderer* Renderer() { return m_renderer; }

    private:
        int m_width;
        int m_height;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
    };
}