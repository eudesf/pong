#include <stdio.h>
#include "common.h"
#include "graphics.h"
#include "input.h"
#include "audio.h"

int main(int argc, char* argv[])
{
    g_startup();
    a_startup();
    
    i_handleEvents();

    a_finalize();
    g_finalize();

    return 0;
}
