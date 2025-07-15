#pragma once

#include <iostream>
#include <stdexcept>  //for errors and shii
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* ______________________________________________________________________________
    OK, SO, BASICALLY IF I GET ANY MINOR INITIALIZATION ERROR, I QUIT EVERYTHING.
    MAKE SURE YALL DO THAT 
    _____________________________________________________________________________
*/

class SDLApp
{
public:
    int width, height;
    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;
    int IMG_FLAGS = IMG_INIT_PNG | IMG_INIT_WEBP | IMG_INIT_JPG;
    SDLApp(int windowWidth, int windowHeight, const char *title)
        : width(windowWidth), height(windowHeight)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            throw std::runtime_error("SDL Initialization Failed");
        }

        if(IMG_Init(IMG_FLAGS) < 0){
            std::cerr << "Failed to initialize image" << IMG_GetError() << std::endl;
            throw std::runtime_error("IMG failed");
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