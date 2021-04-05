#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "Renderer.h"

namespace phys
{
    class Texture
    {
    public:
        Texture(const std::string& filename, Renderer& renderer)
        : m_filename{ filename}, m_renderer{ &renderer }
        {
            SDL_Surface* surface = SDL_LoadBMP(m_filename.c_str());
	        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            m_texture = SDL_CreateTextureFromSurface(m_renderer->Get_Renderer(), surface);
            SDL_FreeSurface(surface);
            m_ref_count++;
        }

        Texture(const Texture& texture)
        : m_texture{ texture.m_texture }, m_renderer{ texture.m_renderer }, m_filename{ texture.m_filename }
        {
            m_ref_count++;
        }

        Texture(const Texture&& texture)
        : m_texture{ texture.m_texture }, m_renderer{ texture.m_renderer }, m_filename{ texture.m_filename }
        {
            m_ref_count++;
        }

        ~Texture() { if(--m_ref_count == 0) SDL_DestroyTexture(m_texture); }
        
        void Draw(const SDL_Rect& rect)
        {
            SDL_RenderCopy(m_renderer->Get_Renderer(), m_texture, NULL, &rect);
        }
        SDL_Texture* Get_Texture() { return m_texture; }
        std::string Filename() { return m_filename; }
    
    private:
        SDL_Texture* m_texture;
        Renderer* m_renderer;
        std::string m_filename;
        inline static int m_ref_count;
    };
}