#include <iostream>
#include <vector>
#include <unordered_map>

#include "Window.h"
#include "Texture.h"
#include "Clock.h"
#include "Particle.h"
#include "Vec.h"
#include "Thread.h"
#include "Renderer.h"
#include "Init_SDL.h"
#include "Space.h"

namespace phys
{
    long long dframes = 0;
    long long pframes = 0;
    bool pause = false;
    phys::Space* space;
    phys::Window* window;
    double zoom = 100;
    phys::Vector camera = phys::Vector{0,0,0};

    int physics(void*)
    {
        phys::Clock clock;
        while(!window->Should_Quit())
        {
            if(!pause)
            {
                clock.Resume();
                while(!pause)
                {
                    space->Update(clock.Lap());
                    pframes++;
                }
                clock.Stop();
            }
        }
        return 0;
    }

    int display(void*)
    {
        phys::Renderer renderer(*window);
        phys::Texture texture("ball.bmp", renderer);
        while(!window->Should_Quit())
        {
            renderer.Clear();
            for(auto& i : space->particles)
            {
                int x = (i.position.x - camera.x - i.radius) * zoom + window->Width() / 2;
                int y = window->Height() / 2 - (i.position.y - camera.y + i.radius) * zoom;
                int rad = i.radius * 2 * zoom;
                texture.Draw(x, y, rad, rad);
            }
            for(auto& i : space->obstacles)
            {
                int x = (i.position.x - camera.x - i.radius) * zoom + window->Width() / 2;
                int y = window->Height() / 2 - (i.position.y - camera.y + i.radius) * zoom;
                int rad = i.radius * 2 * zoom;
                texture.Draw(x, y, rad, rad);
            }
            renderer.Update();
            dframes++;
        }
        return 0;
    }

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
    phys::window = &window;
    phys::space = &space;
    phys::Thread phys_thread(phys::physics, "Physics Thread", NULL);
    phys::Thread disp_thread(phys::display, "Display Thread", NULL);
    while(!window.Should_Quit())
    {
        window.Poll_Events();

    }
    phys::pause = true;
    phys_thread.Wait();
    disp_thread.Wait();
    std::cout << phys::pframes/phys::dframes << std::endl;
}