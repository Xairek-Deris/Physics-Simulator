#include <iostream>
#include <vector>

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
    disp::Window* window;
    double ratio = 100;
    phys::Vector camera = phys::Vector{0,0,0};

    int physics(void*)
    {
        tick::Clock clock;
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
        disp::Renderer renderer(*window);
        disp::Texture texture("ball.bmp", renderer);
        while(!window->Should_Quit())
        {
            renderer.Clear();
            for(auto& i : space->particles)
            {
                int x = (i.position.x - camera.x - i.radius) * ratio + window->Width() / 2;
                int y = window->Height() / 2 - (i.position.y - camera.y + i.radius) * ratio;
                int rad = i.radius * 2 * ratio;
                texture.Draw(x, y, rad, rad);
            }
            for(auto& i : space->obstacles)
            {
                int x = (i.position.x - camera.x - i.radius) * ratio + window->Width() / 2;
                int y = window->Height() / 2 - (i.position.y - camera.y + i.radius) * ratio;
                int rad = i.radius * 2 * ratio;
                texture.Draw(x, y, rad, rad);
            }
            renderer.Update();
            dframes++;
        }
        return 0;
    }
}

int main(int argc, char** argv)
{
    disp::Init();
    disp::Window window("Simulation", 1280, 1280);
    phys::Space space;
    phys::window = &window;
    phys::space = &space;
    win::Thread phys_thread(phys::physics, "Physics Thread", NULL);
    win::Thread disp_thread(phys::display, "Display Thread", NULL);
    while(!window.Should_Quit())
    {
        window.Poll_Events();
    }
    phys::pause = true;
    phys_thread.Wait();
    disp_thread.Wait();
    std::cout << phys::pframes/phys::dframes << std::endl;
}