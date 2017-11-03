#include "ball.h"
#include <math.h>
#include "pong.h"
#include "paddle.h"

#define BALL_SIZE (10)

typedef struct {
    int x;
    int y;
    int velX;
    int velY;
} Ball;

Ball ball;

void prepareBall() {
    ball.x = ceil(mainViewport.w - BALL_SIZE) / 2;
    ball.y = ceil(mainViewport.h - BALL_SIZE) / 2;
    if (ball.velX == 0 && ball.velY == 0) {
        ball.velX = ball.velY = 6;        
    }
}

void drawBall() {
    SDL_Rect ballRect;
    ballRect.x = ball.x;
    ballRect.y = ball.y;
    ballRect.w = ballRect.h = BALL_SIZE;

    SDL_SetRenderDrawColor(graphics.renderer, 0x00, 0x00, 0x00, 0xFF);    
    SDL_RenderFillRect(graphics.renderer, &ballRect);
}

CollisionType checkCollision() {

    if (ball.velX > 0) {
        if (ball.x + BALL_SIZE + ball.velX > mainViewport.w) {
            ball.x = mainViewport.w - BALL_SIZE;
            ball.velX *= -1;
            return RIGHT_EDGE_COLLISION;
            
        } else if (ball.y >= rightPaddle.rect.y && ball.y <= rightPaddle.rect.y + rightPaddle.rect.h
            && ball.x < rightPaddle.rect.x && ball.x + BALL_SIZE + ball.velX >= rightPaddle.rect.x) {
            ball.x = rightPaddle.rect.x - BALL_SIZE;
            ball.velX *= -1;
            return RIGHT_PADDLE_COLLISION;
        }
    } else {
        if (ball.x + ball.velX < 0) {
            ball.x = 0;
            ball.velX *= -1;
            return LEFT_EDGE_COLLISION;
            
        } else if ( ball.y >= leftPaddle.rect.y && ball.y <= leftPaddle.rect.y + leftPaddle.rect.h
                    && ball.x > leftPaddle.rect.x + leftPaddle.rect.w
                    && ball.x + ball.velX <= leftPaddle.rect.x + leftPaddle.rect.w) {
            ball.velX *= -1;
            ball.x = leftPaddle.rect.x + leftPaddle.rect.w;
            return LEFT_PADDLE_COLLISION;
        }
    }

    if (ball.velY > 0) {
        if (ball.y + BALL_SIZE + ball.velY > mainViewport.h) {
            ball.y = mainViewport.h - BALL_SIZE;
            ball.velY *= -1;
            return BOTTOM_EDGE_COLLISION;
        }
    } else if (ball.y + ball.velY < 0) {
        ball.y = 0;
        ball.velY *= -1;
        return TOP_EDGE_COLLISION;
    }

    

    return NO_COLLISION;
}

void moveBall() {

    CollisionType collisionType = checkCollision();

    if (collisionType == LEFT_EDGE_COLLISION) {
        printf("Left Player point!\n");
    } else if (collisionType == RIGHT_EDGE_COLLISION) {
        printf("Right Player point!\n");
    }

    ball.x += ball.velX;
    ball.y += ball.velY;

}
