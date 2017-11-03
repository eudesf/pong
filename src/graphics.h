#pragma once

#include "common.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
} BaseGraphics;

extern BaseGraphics graphics;

int g_startup();

void g_finalize();
