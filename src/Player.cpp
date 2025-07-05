#include "../headers/Player.h"

Player::Player(int gridSize, SDL_Rect rect)
    : playerRect(rect), gridSize(gridSize), lastMoveTime(0), moveDelay(100) {}
void Player::update(const Uint8 *keystates)
{
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

void Player::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &playerRect);
}