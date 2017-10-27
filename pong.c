#include <stdio.h>
#include <SDL.h>
#include <SDL_timer.h>

typedef struct {
    SDL_Window* win;
} Pong;

Pong pong;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

SDL_Window* createWindow() {
    SDL_Window* win = SDL_CreateWindow("Pong",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!win) {
        printf("error creating window: %s\n", SDL_GetError());
        return 0;
    }
    return win;
}

bool startup() {
    if (!init()) {
        return false;
    }
    pong.win = createWindow();
    if (!pong.win) {
        return false;
    }
   
    return true;
}

void finalize() {
    SDL_Quit();
    if (pong.win) {
        SDL_DestroyWindow(pong.win);
    }
}

int main(int argc, char* argv[])
{
    if (!startup()) {
        printf("Error starting... quit");
    } else {
        printf("Yep... started up!");
        SDL_Delay(2000);
    }
    finalize();
}
