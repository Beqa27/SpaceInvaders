#pragma once
#include "includes.h"

class Enemy{
    public:
    int speed;
    SDL_Rect alienRect;
    SDL_Texture* enemyTexture;
    Uint32 lastMoveTime;
    const Uint32 moveCooldown;
    float targetX;
    float targetY;
    Uint32 moveStartTime;
    const Uint32 moveDuration = 500;
    

    Enemy(SDL_Renderer * renderer, int speed, SDL_Rect alienRect, const char * enemySpreite);
    ~Enemy();

    void update();
    void draw(SDL_Renderer* renderer);
};