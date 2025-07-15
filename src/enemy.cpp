#include "../headers/enemy.h"

Enemy::Enemy(SDL_Renderer * renderer, int speed, SDL_Rect alienRect, const char * enemyPath) : speed(speed), alienRect(alienRect) {
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
void Enemy::update(){
    alienRect.x += speed;

    // Check if it hit the left or right border
    if(alienRect.x <= 0 || alienRect.x + alienRect.w >= 800){
        speed = -speed;
    }
}

void Enemy::draw(SDL_Renderer* renderer) {
    if (enemyTexture) {
        SDL_RenderCopy(renderer, enemyTexture, NULL, &alienRect);
    }
}
