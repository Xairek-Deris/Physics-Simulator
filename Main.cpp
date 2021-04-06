#include <iostream>
#include <vector>

#include <stdio.h>

#include <SDL2/SDL.h>

#include "Events.h"
#include "Button.h"
#include "Window.h"
#include "Clock.h"
#include "Particle.h"
#include "Vec.h"
#include "Engine.h"
#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"

namespace phys
{
    long long dframes = 0;
    long long pframes = 0;

    void Func(void* data)
    {
        #define ENG (*(phys::Engine*)(data))
        if(ENG.pause)
            ENG.pause = false;
        else ENG.pause = true;
    }
}

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }
    phys::Window window("Simulation", 1280, 1280);
    phys::Renderer renderer(window);
    std::vector<phys::Texture> textures;
    phys::Texture texture{"ball.bmp", renderer};
    std::vector<phys::Particle> particles;
    std::vector<phys::Particle> obstacles;
    std::vector<phys::Camera> cameras;
    phys::Engine engine(particles, obstacles, cameras);

    //Manually add more particles here
    particles.push_back({ { -5, 0, 0 }, { .1, 0, 0 }, 9, -.001, 1, .1});
    particles.push_back({ { 5, 0, 0 }, { -1, 0, 0 }, 10, 0.001, 1, .1});
    particles.push_back({ { 0, -5, 0 }, { 0, 1, 0 }, 6, 0.001, 1, .1});
    particles.push_back({ { 0, 5, 0 }, { 0, -1, 0 }, 20, -.001, 1, .1});


    //will support more cameras, hardcoding until then
    cameras.push_back( phys::Camera({ 0, 0, 0 }, { 0, 0, 0 }, 10) );
    int active_cam = 0;

    engine.speed = 1;
    engine.Start();


    while(!window.Should_Quit())
    {
        //Event Handling
        while(window.Poll_Event() != 0)
        {
            switch(window.Event().type)
            {
            case SDL_KEYDOWN:
                if(window.Event().key.keysym.scancode == SDL_SCANCODE_SPACE)
                    if(engine.pause)
                        engine.pause = false;
                    else engine.pause = true;
                else if(window.Event().key.keysym.scancode == SDL_SCANCODE_E)
                    engine.speed *= -1;
                break;
            }
        }
        //Drawing Area
        renderer.Clear();
        SDL_Rect rect;
        phys::Camera* camera = &cameras[active_cam];
        for(auto& i : particles)
        {
            rect.x = (i.position.x - camera->position.x - i.radius) * camera->zoom + window.Width() / 2;
            rect.y = window.Height() / 2 - (i.position.y - camera->position.y + i.radius) * camera->zoom;
            rect.w = i.radius * 2 * camera->zoom;
            rect.h = i.radius * 2 * camera->zoom;
            texture.Draw(rect);
        }
        for(auto& i : obstacles)
        {
            rect.x = (i.position.x - camera->position.x - i.radius) * camera->zoom + window.Width() / 2;
            rect.y = window.Height() / 2 - (i.position.y - camera->position.y + i.radius) * camera->zoom;
            rect.w = i.radius * 2 * camera->zoom;
            rect.h = i.radius * 2 * camera->zoom;
            texture.Draw(rect);
        }
        renderer.Display();
        phys::dframes++;
    }
    engine.Stop();
    std::cout << phys::pframes/phys::dframes << std::endl;
}