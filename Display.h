#pragma once

#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>

#include "Camera.h"
#include "Particle.h"
#include "Space.h"
#include "Window.h"

namespace phys
{
    class Display
    {
    public:
        Display(Window& window)
        : m_window{ &window }
        {
            m_renderer = SDL_CreateRenderer(window.m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }

        std::vector<std::pair<SDL_Texture*, std::string>> textures;

        int New_Texture(const std::string& filename);
        void Delete_Texture(int index) { textures[index].second = ""; SDL_DestroyTexture(textures[index].first); }
        void Clear() { SDL_RenderClear(m_renderer); }
        void Update() { SDL_RenderPresent(m_renderer); }
        void Draw_Particles(const std::vector<Particle>& particles, const Camera& camera);
    private:
        Window* m_window;
        SDL_Renderer* m_renderer;
    };
}