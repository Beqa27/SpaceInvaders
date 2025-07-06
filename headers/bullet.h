#pragma once
#include <SDL2/SDL.h>

class Bullet {
public:
    int speed;
    SDL_Rect bulletRect;
    float bulletPosY;

    Bullet(int speed, SDL_Rect playerRect);
    void update();
    void draw(SDL_Renderer* renderer);
    bool isOffScreen(); 
};
