#include "graphics.h"
#include "paddle.h"

#define PADDLE_STEP (20);

Paddle leftPaddle;
Paddle rightPaddle;

void preparePaddles() {
    leftPaddle.direction = 1;
    leftPaddle.position = 0;
    rightPaddle.direction = -1;
    rightPaddle.position = 0;
}

void drawPaddle(Paddle* paddle) {
    SDL_Rect viewPort;
    SDL_RenderGetViewport(graphics.renderer, &viewPort);

    paddle->rect.y = paddle->position + (viewPort.h - PADDLE_HEIGHT) / 2;
    paddle->rect.h = PADDLE_HEIGHT;
    paddle->rect.w = PADDLE_WIDTH;
    paddle->rect.x = PADDLE_SPACEMENT * paddle->direction;
    if (paddle->rect.x < 0) {
        paddle->rect.x += viewPort.w - paddle->rect.w;
    }

    SDL_SetRenderDrawColor(graphics.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(graphics.renderer, &paddle->rect);
}

void drawPaddles() {
    drawPaddle(&leftPaddle);
    drawPaddle(&rightPaddle);
}

void handlePaddleAction(PaddleAction paddleAction) {
    switch (paddleAction) {
    case LEFT_PADDLE_UP: leftPaddle.position -= PADDLE_STEP; break;
    case LEFT_PADDLE_DOWN: leftPaddle.position += PADDLE_STEP; break;
    case RIGHT_PADDLE_UP: rightPaddle.position -= PADDLE_STEP; break;
    case RIGHT_PADDLE_DOWN: rightPaddle.position += PADDLE_STEP; break;
    default: break;
    }
}
