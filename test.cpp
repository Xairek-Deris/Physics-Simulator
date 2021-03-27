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

long long dframes = 0;
long long pframes = 0;
bool quit = false;
bool pause = false;
phys::Space* g_space;
disp::Renderer* g_renderer;
disp::Window* g_window;
disp::Texture* g_texture;
double ratio = 100;

int physics(void*)
{
    tick::Clock clock;
    while(!quit)
    {
        if(!pause)
        {
            clock.Resume();
            while(!pause)
            {
                g_space->Update(clock.Lap());
                pframes++;
            }
            clock.Stop();
        }
    }
    return 0;
}

int display(void*)
{
    while(!quit)
    {
        g_renderer->Clear();
        for(auto& i : g_space->particles)
        {
            g_texture->Draw((i.position.x - i.radius) * ratio, g_window->Height() - (i.position.y + i.radius) * ratio, i.radius * 2 * ratio, i.radius * 2 * ratio);
        }
        for(auto& i : g_space->obstacles)
        {
            g_texture->Draw((i.position.x - i.radius) * ratio, g_window->Height() - (i.position.y + i.radius) * ratio, i.radius * 2 * ratio, i.radius * 2 * ratio);
        }
        g_renderer->Update();
        dframes++;
    }
    return 0;
}

int main(int argc, char** argv)
{
    disp::Init();
    disp::Window window("Simulation", 1280, 1280);
    disp::Renderer renderer(window);
    disp::Texture texture("ball.bmp", renderer);
    phys::Space space;
    g_window = &window;
    g_renderer = &renderer;
    g_texture = &texture;
    g_space = &space;
    space.particles.push_back(phys::Particle(phys::Vector{1,10,0}, phys::Vector{1,0,0}, 10, 0.001, 1, 1));
    space.particles.push_back(phys::Particle(phys::Vector{10,9,2}, phys::Vector{0,0,0}, 10, -0.001, 1, 1));
    space.obstacles.push_back(phys::Particle(phys::Vector{6, -6360000, 0}, phys::Vector{0,0,0}, 5.97e24, 0, 6360000, 1));
    space.obstacles.push_back(phys::Particle(phys::Vector{-6360000, 6, 0}, phys::Vector{0,0,0}, 0, 0, 6360000, 1));
    space.obstacles.push_back(phys::Particle(phys::Vector{6360012.80, 6, 0}, phys::Vector{0,0,0}, 0, 0, 6360000, 1));
    win::Thread phys_thread(physics, "Physics Thread", NULL);
    win::Thread disp_thread(display, "Display Thread", NULL);
    while(!window.Should_Quit())
    {
        window.Poll_Events();
    }
    quit = true;
    pause = true;
    phys_thread.Wait();
    disp_thread.Wait();
    std::cout << pframes/dframes << std::endl;
}