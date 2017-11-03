#pragma once

#include "graphics.h"

typedef enum {NO_COLLISION, LEFT_EDGE_COLLISION, RIGHT_EDGE_COLLISION, TOP_EDGE_COLLISION, BOTTOM_EDGE_COLLISION, RIGHT_PADDLE_COLLISION, LEFT_PADDLE_COLLISION} CollisionType;

void prepareBall();
void drawBall();
void moveBall();

