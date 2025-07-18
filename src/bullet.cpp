#include "../headers/bullet.h"


Bullet::Bullet(int speed, SDL_Rect playerRect) : speed(speed)
{
    bulletRect.w = 8; // Diameter of the circle
    bulletRect.h = 8; // Diameter of the circle

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
    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange color

    // Draw a filled circle (approximated with multiple lines)
    int centerX = bulletRect.x + bulletRect.w / 2;
    int centerY = bulletRect.y + bulletRect.h / 2;
    int radius = bulletRect.w / 2;

    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

bool Bullet::isOffScreen()
{
    return bulletRect.y + bulletRect.h < 0;
}
