#include "../headers/includes.h"

// #define SDL_MAIN_HANDLED

int main()
{
    // I IMPORTED CLASS SO CODE LOOKS OVERALL CLEANER
    SDLApp app(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Invaders");
    Player spaceship = Player(app.renderer, 6, {WINDOW_WIDTH / 2, WINDOW_HEIGHT -  96, 96, 96}, "assets/ship.png");
    Enemy alien = Enemy(app.renderer, 10, {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 72, 72}, "assets/alien.png"); // 48 * 1.5 = 72
    SDL_Event e;
    bool running = true;
    bool enemyAlive = true;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // UPDATE LOOP
        const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
        spaceship.update(keystates);
        if (enemyAlive) {
            alien.update();
        }

        // Bullet-enemy collision detection
        if (enemyAlive) {
            for (auto it = spaceship.bullets.begin(); it != spaceship.bullets.end(); ) {
                if (SDL_HasIntersection(&it->bulletRect, &alien.alienRect)) {
                    // Collision detected: destroy enemy and bullet
                    enemyAlive = false;
                    it = spaceship.bullets.erase(it);
                } else {
                    ++it;
                }
            }
        }

        // Check for collision with bottom of the screen
        if (alien.alienRect.y + alien.alienRect.h >= WINDOW_HEIGHT) {
            running = false; // Close the game
        }

        // Check for collision with player
        if (SDL_HasIntersection(&alien.alienRect, &spaceship.playerRect)) {
            running = false; // Close the game
        }

        // DRAW STUFF HERE
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
        SDL_RenderClear(app.renderer);
        app.renderBackground();

        spaceship.draw(app.renderer);
        if (enemyAlive) {
            alien.draw(app.renderer);
        }

        SDL_RenderPresent(app.renderer);

        // TS IS MEASURED IN MILLISECONDS SO IM DOING 60 FPS
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();

    return 0;
}
