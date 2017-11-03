#include "input.h"
#include "paddle.h"
#include "ball.h"

#define MILLIS_PER_FRAME (16)

void i_handleEvents() {

    preparePaddles();
    prepareBall();
    SDL_Event event;
    PaddleAction paddleAction;

    while (1) {
        long millis = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            paddleAction = NO_PADDLE_ACTION;
            switch (event.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_UP: paddleAction = RIGHT_PADDLE_UP; break;
                case SDLK_DOWN: paddleAction = RIGHT_PADDLE_DOWN; break;
                case SDLK_w: paddleAction = LEFT_PADDLE_UP; break;
                case SDLK_s: paddleAction = LEFT_PADDLE_DOWN; break;
                }
            }
            handlePaddleAction(paddleAction);
        }
        p_render();
        millis = SDL_GetTicks() - millis;
        if (millis < MILLIS_PER_FRAME) {
            SDL_Delay(MILLIS_PER_FRAME - millis);
        }

    }
}
