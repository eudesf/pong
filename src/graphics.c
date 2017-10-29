#include "graphics.h"

BaseGraphics graphics;

int g_startup() {

    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Creating Main Window
    graphics.window = SDL_CreateWindow("Pong",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!graphics.window) {
        printf("error creating window: %s\n", SDL_GetError());
        return -1;
    }

    // Creating Renderer
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    graphics.renderer = SDL_CreateRenderer(graphics.window, -1, render_flags);
    if (!graphics.renderer) {
        printf("error creating renderer: %s\n", SDL_GetError());
        return -1;
    }

    graphics.surface = SDL_GetWindowSurface(graphics.window);
    
    return 0;
}

void g_finalize() {
    SDL_Quit();
    if (graphics.window) {
        SDL_DestroyWindow(graphics.window);
        if (graphics.renderer) {
            SDL_DestroyRenderer(graphics.renderer);
        }
    }

}
