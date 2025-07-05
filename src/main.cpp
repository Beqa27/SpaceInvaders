#include "../headers/includes.h"
#include "../headers/Player.h"
//#define SDL_MAIN_HANDLED

int main(){
    // I IMPORTED CLASS SO CODE LOOKS OVERALL CLEANER
    SDLApp app(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Invaders");
    Player spaceship = Player(32, {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 10, 10});
    SDL_Event e;
    bool running = true;

    while (running)
    {
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
        }
        const Uint8 * keystates = SDL_GetKeyboardState(nullptr);
        spaceship.update(keystates);

        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
        
        SDL_RenderClear(app.renderer);

        spaceship.draw(app.renderer);

        SDL_RenderPresent(app.renderer);
    }

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    
    return 0;
}