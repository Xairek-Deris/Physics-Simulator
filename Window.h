#include <SDL2/SDL.h>
#include <iostream>
namespace win
{
    static bool sdl_initialized = false;

    class Texture;

    class Window
    {
    public:
        Window(const char * title, int width, int height);

        ~Window()
        {
            SDL_DestroyWindow(m_window);
        }

        void Update() { SDL_RenderPresent(m_renderer); }
        void Clear() { SDL_RenderClear(m_renderer); }
        int Height() {return m_height;}
        int Width() {return m_width;}
        void Resize(int width, int height) {m_width = width; m_height = height;}

    private:
        int m_width;
        int m_height;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        friend Texture::Texture(const char* file, Window* window);
    };
}