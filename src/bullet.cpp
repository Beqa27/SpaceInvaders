#include "../headers/bullet.h"


Bullet::Bullet(int speed, SDL_Rect playerRect) : speed(speed)
{
    bulletRect.w = 4;
    bulletRect.h = 10;

    // Start bullet at center of player
    bulletRect.x = playerRect.x + (playerRect.w / 2) - (bulletRect.w / 2);
    bulletRect.y = playerRect.y;

    bulletPosY = static_cast<float>(bulletRect.y);
}

void Bullet::update()
{
    bulletPosY -= speed;
    bulletRect.y = static_cast<int>(bulletPosY);
}

void Bullet::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
    SDL_RenderFillRect(renderer, &bulletRect);
}

bool Bullet::isOffScreen()
{
    return bulletRect.y + bulletRect.h < 0;
}
