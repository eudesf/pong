#include <stdio.h>
#include <SDL2/SDL.h>
#include "graphics.h"
#include "input.h"

int main(int argc, char* argv[])
{
    g_startup();

    i_handleEvents();
    
    g_finalize();

    return 0;
}
