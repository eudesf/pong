#include "input.h"
#include "paddle.h"

void i_handleEvents() {

    preparePaddles();
    SDL_Event event;

    while (1) {
        while (SDL_PollEvent(&event)) {
            PaddleAction paddleAction = NO_PADDLE_ACTION;
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
            p_render();
            SDL_Delay(10);
        }
    }
}
