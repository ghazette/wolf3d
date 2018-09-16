#include "../../includes/wolf3d.h"

void    exitprogram_evt(t_sdl *sdl)
{
    destroy_sdl(sdl);
    exit(0);
}