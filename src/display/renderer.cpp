#include "renderer.h"

int disp::Renderer::ref_count_;

disp::Renderer::Renderer(Window& window)
: window_{ &window }
{
    renderer_ = SDL_CreateRenderer(window_->window(), -1, 
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
    ref_count_++;
}

disp::Renderer::Renderer(const Renderer& renderer)
: window_{ renderer.window_ }, renderer_{ renderer.renderer_ }
{
    ref_count_++;
}

disp::Renderer::Renderer(const Renderer&& renderer)
: window_{ renderer.window_ }, renderer_{ renderer.renderer_ }
{
    ref_count_++;
}

disp::Renderer::~Renderer()
{
    if(--ref_count_ == 0) 
        SDL_DestroyRenderer(renderer_);
}