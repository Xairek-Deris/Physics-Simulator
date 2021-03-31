#include <iostream>
#include <vector>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "Window.h"
#include "Clock.h"
#include "Particle.h"
#include "Vec.h"
#include "Space.h"
#include "Engine.h"
#include "Display.h"
#include "Camera.h"

namespace phys
{
    long long dframes = 0;
    long long pframes = 0;

    enum class cmd
    {
        INVALID,
        PAUSE,
        UNPAUSE,
        LOAD_SPACE,
        SAVE_SPACE,
        NEW,
        DELETE,
        EDIT,
        CAMERA,
        ZOOM,
        QUIT,
        HELP
    };

    std::unordered_map<std::string, cmd> cmd_map 
    {
        {"load", cmd::LOAD_SPACE},
        {"save", cmd::SAVE_SPACE},
        {"pause", cmd::PAUSE},
        {"unpause", cmd::UNPAUSE},
        {"new", cmd::NEW},
        {"delete", cmd::DELETE}, 
        {"edit", cmd::EDIT},
        {"camera", cmd::CAMERA},
        {"zoom", cmd::ZOOM},
        {"quit", cmd::QUIT},
        {"help", cmd::HELP}
    };
}

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    phys::Window window("Simulation", 1280, 1280);
    phys::Display display(window);
    phys::Space space;
    phys::Engine engine(space);
    space.particles.push_back(phys::Particle{ phys::Vector{ 0,0,0 }, phys::Vector{ 1,0,0}, 10, 1, 1, 1, 0});
    space.cameras.push_back( phys::Camera(phys::Vector{0, 0, 0}, phys::Vector{ 0, 1, 0 }, 100) );
    display.New_Texture("ball.bmp");
    engine.Start();
    while(!window.Should_Quit())
    {
        window.Poll_Events();
        display.Clear();
        display.Draw_Particles(space.particles, space.cameras[0]);
        display.Update();
        phys::dframes++;
    }
    engine.Stop();
    std::cout << phys::pframes/phys::dframes << std::endl;
}