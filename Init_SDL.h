#include <iostream>

#include <SDL2/SDL.h>

namespace phys
{
    int Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }
    return 0;
}
}