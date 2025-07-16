#include "../headers/enemy.h"

Enemy::Enemy(SDL_Renderer * renderer, int speed, SDL_Rect alienRect, const char * enemyPath) : speed(speed), alienRect(alienRect), lastMoveTime(0), moveCooldown(1000) {
    enemyTexture = IMG_LoadTexture(renderer, enemyPath);
    if(!enemyTexture){
        std::cerr << "failed to load texture" << std::endl;
    }
}

Enemy::~Enemy(){
    if(enemyTexture){
        SDL_DestroyTexture(enemyTexture);
    }
}
void Enemy::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime > moveCooldown) {
        // Move horizontally in steps
        alienRect.x += speed;

        // Check if it hits the wall
        if (alienRect.x <= 0 || alienRect.x + alienRect.w >= 800) {
            // Reverse direction
            speed = -speed;

            // Move down when hitting wall
            alienRect.y += 10;

            // Make sure it doesn't "double move" left/right on next tick
            alienRect.x += speed; 
        }

        lastMoveTime = currentTime;
    }
}


void Enemy::draw(SDL_Renderer* renderer) {
    if (enemyTexture) {
        SDL_RenderCopy(renderer, enemyTexture, NULL, &alienRect);
    }
}
