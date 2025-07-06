#include "../headers/Player.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Player::Player(SDL_Renderer *renderer, int gridSize, SDL_Rect rect, const char *texturePath)
    : playerRect(rect), gridSize(gridSize), lastMoveTime(0), moveDelay(100)
{

    playerTexture = IMG_LoadTexture(renderer, texturePath);
    if (!playerTexture)
    {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
    }
}
void Player::update(const Uint8 *keystates)
{
    checkBorders();
    Uint32 now = SDL_GetTicks();

    if (now - lastMoveTime < moveDelay)
        return;

    if (keystates[SDL_SCANCODE_A])
        playerRect.x -= gridSize;
    else if (keystates[SDL_SCANCODE_D])
        playerRect.x += gridSize;
    else
        return;

    lastMoveTime = now;
}
Player::~Player()
{
    if (playerTexture)
    {
        SDL_DestroyTexture(playerTexture);
    }
}
void Player::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Point center = {playerRect.w / 2, playerRect.h / 2};
    SDL_RenderCopyEx(renderer, playerTexture, nullptr, &playerRect, 0, &center, SDL_FLIP_NONE);
}
void Player::checkBorders(){
    if(playerRect.x < 0) playerRect.x = 0;
    if(playerRect.x + playerRect.w > 800) playerRect.x = 800 - playerRect.w;
}