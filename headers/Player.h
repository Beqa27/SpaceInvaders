#pragma once

#include <SDL2/SDL.h>

class Player
{
public:
    SDL_Rect playerRect;
    int gridSize;
    int moveCooldown = 0;
    int moveDelay = 100;
    Uint32 lastMoveTime = 0;

    Player(int gridSize, SDL_Rect rect);
    void update(const Uint8 *keystates);
    void draw(SDL_Renderer *renderer);
};