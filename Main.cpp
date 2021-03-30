#include <iostream>
#include <vector>
#include <unordered_map>

#include "Window.h"
#include "Clock.h"
#include "Particle.h"
#include "Vec.h"
#include "Init_SDL.h"
#include "Space.h"
#include "Engine.h"
#include "Display.h"

namespace phys
{
    long long dframes = 0;
    long long pframes = 0;

    enum class cmd
    {
        INVALID,
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
    phys::Init();
    phys::Window window("Simulation", 1280, 1280);
    phys::Space space;
    phys::Engine engine(&space);
    engine.Start();
    phys::Display display(window, space, "ball.bmp");
    display.Start();
    while(!window.Should_Quit())
    {
        window.Poll_Events();
    }
    engine.Stop();
    display.Stop();
    std::cout << phys::pframes/phys::dframes << std::endl;
}