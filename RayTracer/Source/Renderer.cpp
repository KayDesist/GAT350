#include "Renderer.h"
#include "Framebuffer.h"

bool Renderer::Initialize()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}

bool Renderer::CreateWindow(int width, int height)
{
    m_width = width;
    m_height = height;
    m_window = SDL_CreateWindow("Game Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    return 0;
}

void Renderer::CopyFramebuffer(const Framebuffer* framebuffer)
{
    SDL_RenderCopy(m_renderer, framebuffer->m_texture, NULL, NULL);
}