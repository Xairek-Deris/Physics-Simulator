#include <iostream>
#include <vector>

#include "Physics/camera.h"
#include "Physics/clock.h"
#include "Physics/particle.h"
#include "Physics/vector.h"
#include "Display/box.h"
#include "Display/point.h"
#include "Display/renderer.h"
#include "Display/texture.h"
#include "Display/thread.h"
#include "Display/window.h"
#include "engine.h"

long long dframes = 0;
long long pframes = 0;

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }
    disp::Window window("Simulation", 1280, 1280);
    disp::Renderer renderer(window);
    std::vector<disp::Texture> textures;
    disp::Texture texture{"res/ball.bmp", renderer};
    std::vector<phys::Particle> particles;
    std::vector<phys::Particle> obstacles;
    std::vector<phys::Camera> cameras;
    
    //Manually add more particles here
    particles.push_back({ { -5, 0, 0 }, { .1, 0, 0 }, 9, -.001, 1, .1});
    particles.push_back({ { 5, 0, 0 }, { -1, 0, 0 }, 10, 0.001, 1, .1});
    particles.push_back({ { 0, -5, 0 }, { 0, 1, 0 }, 6, 0.001, 1, .1});
    particles.push_back({ { 0, 5, 0 }, { 0, -1, 0 }, 20, -.001, 1, .1});

    //will support more cameras, hardcoding until then
    cameras.push_back( phys::Camera({ 0, 0, 0 }, { 0, 0, 0 }, 10) );
    int active_cam = 0;

    phys::Engine engine(particles, obstacles, cameras);
    engine.start();
    while(!window.should_quit())
    {
        //Event Handling
        while(window.poll_event() != 0)
        {
            switch(window.event().type)
            {
            case SDL_KEYDOWN:
                if(window.event().key.keysym.scancode == SDL_SCANCODE_SPACE)
                    if(engine.paused())
                        engine.unpause();
                    else engine.pause();
                else if(window.event().key.keysym.scancode == SDL_SCANCODE_E)
                    engine.set_speed(engine.speed() * -1);
                break;
            }
        }
        //Drawing Area
        renderer.clear();
        disp::Box box;
        phys::Camera* camera = &cameras[active_cam];
        for(auto& i : particles)
        {
            box.set_x((i.position().x() - camera->position().x() - i.radius()) * camera->zoom() + window.width() / 2);
            box.set_y(window.height() / 2 - (i.position().y() - camera->position().y() + i.radius()) * camera->zoom());
            box.set_width(i.radius() * 2 * camera->zoom());
            box.set_height(i.radius() * 2 * camera->zoom());
            texture.draw(box);
        }
        for(auto& i : obstacles)
        {
            box.set_x((i.position().x() - camera->position().x() - i.radius()) * camera->zoom() + window.width() / 2);
            box.set_y(window.height() / 2 - (i.position().y() - camera->position().y() + i.radius()) * camera->zoom());
            box.set_width(i.radius() * 2 * camera->zoom());
            box.set_height(i.radius() * 2 * camera->zoom());
            texture.draw(box);
        }
        renderer.display();
        dframes++;
    }
    engine.stop();
    std::cout << pframes/dframes << std::endl;
}