#include "Renderer.h" 
#include <SDL.h>

bool Renderer::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
}

bool Renderer::CreateWindow(std::string name, int width, int height)
{
    SDL_Window* window = SDL_CreateWindow("Game Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1000, 1000,
        SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    while (true)
    {
        // clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // show screen
        SDL_RenderPresent(renderer);
    }

    return 0;
}
