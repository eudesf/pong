#include "graphics.h"
#include "ball.h"
#include <math.h>
#include <stdlib.h>

typedef struct ParticleStruct {
    int x;
    int y;
    int velX;
    int velY;
    long borntime;
    struct ParticleStruct* next;
} Particle;

Particle* firstParticle;
Particle* lastParticle;

#define MAX_LIFE_TIME (500)
#define CREATION_INTERVAL (1)

long lastTicks;

void createParticle(Particle* particle) {
    particle->velY = floor(ball.velY / 2);
    particle->velX = floor(ball.velX / 2);

    srand(SDL_GetTicks());
    particle->x = ball.x + (rand() % BALL_SIZE);
    particle->y = ball.y + (rand() % BALL_SIZE);

    particle->borntime = SDL_GetTicks();
    particle->next = NULL;
}

void addNewParticle() {
    Particle* newParticle = malloc(sizeof(Particle));
    createParticle(newParticle);
    if (firstParticle == NULL) {
        firstParticle = lastParticle = newParticle;
    } else {
        lastParticle->next = newParticle;
        lastParticle = newParticle;
    }
}

void prepareParticles() {
    lastTicks = SDL_GetTicks();
    addNewParticle();
}

void handleCollision(Particle* particle) {
    SDL_Rect viewPort;
    SDL_RenderGetViewport(graphics.renderer, &viewPort);
    
    if (particle->x < 0)  particle->x = 0;
    if (particle->y < 0)  particle->y = 0;
    if (particle->x+1 > viewPort.w) particle->x = viewPort.w-1;
    if (particle->y+1 > viewPort.h) particle->y = viewPort.h-1;
//    if (particle->x <= 0)  particle->velX *= -1;
//    if (particle->y <= 0)  particle->velY *= -1;
//    if (particle->x+1 > viewPort.w) particle->velX *= -1;
//    if (particle->y+1 > viewPort.h) particle->velY *= -1;
}

void drawParticles() {
    Particle* priorParticle = NULL;
    Particle* particle = firstParticle;

    do {
        long lifetime = SDL_GetTicks() - particle->borntime;
        int color = (lifetime/2) % 0xFF;
            
        SDL_SetRenderDrawColor(graphics.renderer, color, color, color, 0xFF);
        SDL_RenderDrawPoint(graphics.renderer, particle->x, particle->y);
        SDL_RenderDrawPoint(graphics.renderer, particle->x+1, particle->y);
        SDL_RenderDrawPoint(graphics.renderer, particle->x-1, particle->y);
        SDL_RenderDrawPoint(graphics.renderer, particle->x, particle->y+1);
        SDL_RenderDrawPoint(graphics.renderer, particle->x, particle->y-1);
        
        particle->x += particle->velX;
        particle->y += particle->velY;

        handleCollision(particle);

        Particle* nextParticle = particle->next;

        if (lifetime > MAX_LIFE_TIME) {
            if (priorParticle == NULL) {
                firstParticle = particle->next;
            } else if (particle->next != NULL) {
                priorParticle->next = particle->next;
            }
            free(particle);
        }
        particle = nextParticle;
    } while (particle != NULL);

    if (SDL_GetTicks() - lastTicks >= CREATION_INTERVAL) {
        lastTicks = SDL_GetTicks();
        addNewParticle();
    }
}
