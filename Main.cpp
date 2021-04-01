#include <iostream>
#include <vector>

#include <stdio.h>

#include <SDL2/SDL.h>

#include "Window.h"
#include "Clock.h"
#include "Particle.h"
#include "Vec.h"
#include "Space.h"
#include "Engine.h"
#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"

namespace phys
{
    long long dframes = 0;
    long long pframes = 0;
}

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    phys::Window window("Simulation", 1280, 1280);
    phys::Space space;
    phys::Engine engine(space);
    phys::Renderer renderer(window);
    std::vector<phys::Texture> textures;
    textures.push_back(phys::Texture("ball.bmp", renderer));
    space.particles.push_back(phys::Particle{ phys::Vector{ 0, 0, 0 }, phys::Vector{ 0, 0, 0 }, 10, 0, 1, .1, 0});
    space.cameras.push_back( phys::Camera(phys::Vector{ 0, 0, 0 }, phys::Vector{ 0, 0, 0 }, 100) );
    engine.Start();
    bool quit = false;
    int active_cam = 0;
    while(!quit)
    {
        //Event Handling
        while(window.Poll_Event() != 0)
        {
            if(window.Event().type == SDL_QUIT)
                quit = true;
        }
        //Drawing Area
        renderer.Clear();
        SDL_Rect rect {0, 0, 100, 100};
        phys::Camera* camera = &space.cameras[active_cam];
        for(auto& i : space.particles)
        {
            rect.x = (i.position.x - camera->position.x - i.radius) * camera->zoom + window.Width() / 2;
            rect.y = window.Height() / 2 - (i.position.y - camera->position.y + i.radius) * camera->zoom;
            rect.w = i.radius * 2 * camera->zoom;
            rect.h = i.radius * 2 * camera->zoom;
            textures[i.texture].Draw(rect);
        }
        for(auto& i : space.obstacles)
        {
            rect.x = (i.position.x - camera->position.x - i.radius) * camera->zoom + window.Width() / 2;
            rect.y = window.Height() / 2 - (i.position.y - camera->position.y + i.radius) * camera->zoom;
            rect.w = i.radius * 2 * camera->zoom;
            rect.h = i.radius * 2 * camera->zoom;
            textures[i.texture].Draw(rect);
        }
        renderer.Display();
        phys::dframes++;
    }
    engine.Stop();
    std::cout << phys::pframes/phys::dframes << std::endl;
}