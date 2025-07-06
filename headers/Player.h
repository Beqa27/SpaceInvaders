#pragma once

#include <SDL2/SDL.h>

class Player
{
public:
    SDL_Rect playerRect;
    SDL_Texture * playerTexture;
    int gridSize;
    int moveCooldown = 0;
    int moveDelay = 100;
    Uint32 lastMoveTime = 0;

    Player(SDL_Renderer* renderer, int gridSize, SDL_Rect rect, const char * texturePath);
    ~Player();
    void update(const Uint8 *keystates);
    void draw(SDL_Renderer *renderer);
    void checkBorders();
};