#include "texture.h"

int disp::Texture::ref_count_{ 0 };

disp::Texture::Texture(const std::string& f, Renderer& r)
: renderer_{ &r }
{
    SDL_Surface* surface = SDL_LoadBMP(f.c_str());
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    texture_ = SDL_CreateTextureFromSurface(renderer_->renderer(), surface);
    SDL_FreeSurface(surface);
    ref_count_++;
}

disp::Texture::Texture(const Texture& texture)
: texture_{ texture.texture_ }, renderer_{ texture.renderer_ }
{
    ref_count_++;
}

disp::Texture::Texture(const Texture&& texture)
: texture_{ texture.texture_ }, renderer_{ texture.renderer_ }
{
    ref_count_++;
}

disp::Texture disp::Texture::operator=(Texture& t)
{
    texture_ = t.texture_;
    renderer_ = t.renderer_;
    ref_count_++;
}

disp::Texture disp::Texture::operator=(Texture&& t)
{
    texture_ = t.texture_;
    renderer_ = t.renderer_;
    ref_count_++;
}

disp::Texture::~Texture()
{
    if(--ref_count_ == 0)
        SDL_DestroyTexture(texture_);
}