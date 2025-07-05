#pragma once

#include <iostream>
#include <stdexcept> // Required for std::runtime_error
#include <SDL2/SDL.h>

/* _________________________________________
    OK, SO, BASICALLY IF I GET ANY MINOR INITIALIZATION ERROR, I QUIT EVERYTHING.
    MAKE SURE YALL DO THAT TOO SO WE DONT CAUSE MEMORY LEAKS
*/

class SDLApp
{
public:
    int width, height;
    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;

    SDLApp(int windowWidth, int windowHeight, const char *title)
        : width(windowWidth), height(windowHeight)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            throw std::runtime_error("SDL Initialization Failed");
        }

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
            SDL_Quit(); 
            throw std::runtime_error("Window Creation Failed");
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window); 
            SDL_Quit();
            throw std::runtime_error("Renderer Creation Failed");
        }
    }

    ~SDLApp()
    {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    };
};