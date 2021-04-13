#include "display.h"

#include <iostream>

int disp::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }
    return 0;
}