#pragma once

#include "graphics.h"

typedef enum {
    NO_COLLISION,
    LEFT_EDGE_COLLISION,
    RIGHT_EDGE_COLLISION,
    TOP_EDGE_COLLISION,
    BOTTOM_EDGE_COLLISION,
    RIGHT_PADDLE_COLLISION,
    LEFT_PADDLE_COLLISION
} CollisionType;

typedef struct {
    int x;
    int y;
    int velX;
    int velY;
} Ball;

#define BALL_SIZE (20)

extern Ball ball;

void prepareBall();
void drawBall();
void moveBall();

