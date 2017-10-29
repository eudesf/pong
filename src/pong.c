#include <stdio.h>
#include "pong.h"
#include "paddle.h"

#define WINDOW_BORDER (10)

SDL_Rect MAIN_VIEWPORT = {
    WINDOW_BORDER, WINDOW_BORDER,
    WINDOW_WIDTH - (WINDOW_BORDER * 2),
    WINDOW_HEIGHT - (WINDOW_BORDER * 2)};

void p_render() {
    // Border
    SDL_SetRenderDrawColor(graphics.renderer, 0x70, 0x43, 0x00, 0xFF);
    SDL_RenderClear(graphics.renderer);

    // Main Viewport
    SDL_RenderSetViewport(graphics.renderer, &MAIN_VIEWPORT);

    // Viewport Color Fill
    SDL_Rect viewportRect = {0, 0, MAIN_VIEWPORT.w, MAIN_VIEWPORT.h};
    SDL_SetRenderDrawColor(graphics.renderer, 0xD4, 0x83, 0x0C, 0xFF);
    SDL_RenderFillRect(graphics.renderer, &viewportRect);

    // Middle Line
    SDL_SetRenderDrawColor(graphics.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int i = 0; i < MAIN_VIEWPORT.h; i++) {
        if (i % 8 < 4) {
            SDL_RenderDrawPoint(graphics.renderer, MAIN_VIEWPORT.w / 2, i);
        }
    }

    drawPaddles();
    
    SDL_RenderPresent(graphics.renderer);
}
