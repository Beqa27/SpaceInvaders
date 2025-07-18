#include "../headers/enemy.h"

Enemy::Enemy(SDL_Renderer * renderer, int speed, SDL_Rect alienRect, const char * enemyPath) : speed(speed * 2), alienRect(alienRect), lastMoveTime(0), moveCooldown(1000), targetX(static_cast<float>(alienRect.x)), targetY(static_cast<float>(alienRect.y)), moveStartTime(0) {
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

    if (currentTime - moveStartTime < moveDuration) {
        // Interpolate movement
        float t = static_cast<float>(currentTime - moveStartTime) / moveDuration;
        alienRect.x = static_cast<int>(alienRect.x + (targetX - alienRect.x) * t);
        alienRect.y = static_cast<int>(alienRect.y + (targetY - alienRect.y) * t);
    } else {
        // Movement complete, set new target
        alienRect.x = static_cast<int>(targetX);
        alienRect.y = static_cast<int>(targetY);

        if (currentTime - lastMoveTime > moveCooldown) {
            // Calculate next target position
            int nextX = alienRect.x + speed;
            int nextY = alienRect.y;

            // Check for wall collision
            if (nextX <= 0 || nextX + alienRect.w >= WINDOW_WIDTH) {
                speed = -speed;
                nextY += 50; // Increased vertical jump
            }
            nextX = alienRect.x + speed;

            targetX = static_cast<float>(nextX);
            targetY = static_cast<float>(nextY);
            moveStartTime = currentTime;
            lastMoveTime = currentTime;
        }
    }
}
//kills the 80s style, but makes the enemy fit more with the new style

void Enemy::draw(SDL_Renderer* renderer) {
    if (enemyTexture) {
        SDL_RenderCopyEx(renderer, enemyTexture, NULL, &alienRect, 0, NULL, SDL_FLIP_VERTICAL);
    }
}
