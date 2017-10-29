#pragma once

#include "graphics.h"

typedef struct {
    SDL_Rect rect;
    int direction;
    int position;
} Paddle;

extern Paddle leftPaddle;
extern Paddle rightPaddle;

#define PADDLE_WIDTH (15)
#define PADDLE_HEIGHT (120)

/* Space between the paddle and the border */
#define PADDLE_SPACEMENT (30)

extern Paddle leftPaddle;
extern Paddle rightPaddle;

void preparePaddles();
void drawPaddles();

typedef enum {NO_PADDLE_ACTION, LEFT_PADDLE_UP, LEFT_PADDLE_DOWN, RIGHT_PADDLE_UP, RIGHT_PADDLE_DOWN} PaddleAction;

void handlePaddleAction(PaddleAction paddleAction);
