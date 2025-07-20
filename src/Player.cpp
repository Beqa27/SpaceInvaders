#include "../headers/Player.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../headers/includes.h"

Player::Player(SDL_Renderer *renderer, int speed, SDL_Rect rect, const char *texturePath)
    : playerRect(rect), speed(speed), lastShotTime(0)
{
    playerTexture = IMG_LoadTexture(renderer, texturePath);
    if (!playerTexture)
    {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
    }
}

Player::~Player()
{
    if (playerTexture)
    {
        SDL_DestroyTexture(playerTexture);
    }
}

void Player::update(const Uint8 *keystates)
{
    move(keystates);
    checkBorders();

    for (auto it = bullets.begin(); it != bullets.end();)
    {
        it->update();
        if (it->isOffScreen())
        {
            it = bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Player::move(const Uint8 *keystates)
{
    if (keystates[SDL_SCANCODE_A]) playerRect.x -= speed;
    if (keystates[SDL_SCANCODE_D]) playerRect.x += speed;
    if (keystates[SDL_SCANCODE_SPACE]) shoot();
}

void Player::shoot()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastShotTime > shootCooldown)
    {
        bullets.emplace_back(10, playerRect);
        lastShotTime = currentTime;
    }
}

void Player::checkBorders()
{
    if (playerRect.x < 0) playerRect.x = 0;
    if (playerRect.x + playerRect.w > WINDOW_WIDTH) playerRect.x = WINDOW_WIDTH - playerRect.w;
}

void Player::draw(SDL_Renderer *renderer)
{
    for (auto &bullet : bullets)
    {
        bullet.draw(renderer);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Point center = {playerRect.w / 2, playerRect.h / 2};
    SDL_RenderCopyEx(renderer, playerTexture, nullptr, &playerRect, 0, &center, SDL_FLIP_NONE);
}