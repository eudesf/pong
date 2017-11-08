#include <stdio.h>
#include "pong.h"
#include "paddle.h"
#include "ball.h"
#include "particles.h"

#define WINDOW_BORDER (10)

SDL_Rect mainViewport = {
    WINDOW_BORDER, WINDOW_BORDER,
    WINDOW_WIDTH - (WINDOW_BORDER * 2),
    WINDOW_HEIGHT - (WINDOW_BORDER * 2)};

void p_render() {
    // Border
    SDL_SetRenderDrawColor(graphics.renderer, 0x70, 0x43, 0x00, 0xFF);
    SDL_RenderClear(graphics.renderer);

    // Main Viewport
    SDL_RenderSetViewport(graphics.renderer, &mainViewport);

    // Viewport Color Fill
    SDL_Rect viewportRect = {0, 0, mainViewport.w, mainViewport.h};
    SDL_SetRenderDrawColor(graphics.renderer, 0xD4, 0x83, 0x0C, 0xFF);
    SDL_RenderFillRect(graphics.renderer, &viewportRect);

    // Middle Line
    SDL_SetRenderDrawColor(graphics.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int i = 0; i < mainViewport.h; i++) {
        if (i % 8 < 4) {
            SDL_RenderDrawPoint(graphics.renderer, mainViewport.w / 2, i);
        }
    }

    drawBall();
    drawParticles();
    drawPaddles();
    moveBall();
    
    SDL_RenderPresent(graphics.renderer);
}
