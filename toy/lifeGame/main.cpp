#include "Game.hpp"

int main(){
    Game<50, 50> game;

    bool stop = false;
    while (!stop) {
        SDL_Event event;
        while (SDL_PollEvent(&event) > 0) {
            if (event.type == SDL_QUIT) {
                stop = true;
            }
        }
        game.draw();
        SDL_Delay(200);
    }
    return 0;
}

