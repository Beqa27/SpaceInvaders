#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdexcept>  //for errors and shii

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
    SDL_Texture* backgroundTexture = nullptr;
    float backgroundY = 0.0f;
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

        backgroundTexture = IMG_LoadTexture(renderer, "assets/background.png");
        if (!backgroundTexture) {
            std::cerr << "Failed to load background texture: " << IMG_GetError() << std::endl;
            // Handle error, but don't necessarily throw if game can proceed without background
        }



    }

    void renderBackground() {
        backgroundY += 0.5f; // Adjust speed as needed

        // Calculate the effective height of one background segment, considering the overlap
        float effectiveHeight = height - 40;

        // If the background has scrolled past one effective segment, reset its position
        if (backgroundY >= effectiveHeight) {
            backgroundY -= effectiveHeight;
        }

        SDL_Rect srcRect = {0, 0, width, height};

        // Draw the first background texture
        SDL_Rect destRect1 = {0, static_cast<int>(backgroundY), width, height};
        SDL_RenderCopy(renderer, backgroundTexture, &srcRect, &destRect1);

        // Draw the second background texture, positioned above the first one with overlap
        SDL_Rect destRect2 = {0, static_cast<int>(backgroundY - effectiveHeight), width, height};
        SDL_RenderCopy(renderer, backgroundTexture, &srcRect, &destRect2);
    }

    

    ~SDLApp()
    {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        if (backgroundTexture) {
            SDL_DestroyTexture(backgroundTexture);
        }
        SDL_Quit();
    };
};