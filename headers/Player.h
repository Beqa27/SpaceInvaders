#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "bullet.h"

class Player {
public:
    SDL_Rect playerRect;
    int speed;
    SDL_Texture* playerTexture;
    std::vector<Bullet> bullets;
    Uint32 lastShotTime;
    const Uint32 shootCooldown = 300;
    

    Player(SDL_Renderer* renderer, int speed, SDL_Rect rect, const char* texturePath);
    ~Player();

    void update(const Uint8* keystates);
    void move(const Uint8* keystates);
    void checkBorders();
    void draw(SDL_Renderer* renderer);
    void shoot();
};