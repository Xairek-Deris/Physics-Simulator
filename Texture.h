#include <SDL2/SDL.h>

namespace win
{
    class Window;

    class Texture
    {
    public:
        Texture(const char* file, Window& window);
        ~Texture() { SDL_DestroyTexture(m_texture); }
        void Draw(int x, int y, int width, int height);

    private:
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;
    };
}