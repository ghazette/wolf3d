#include "../../includes/wolf3d.h"

t_sdl       *init_sdl(t_map *map)
{
    t_sdl *sdl;

    if (!(sdl = malloc(sizeof(t_sdl))))
        return (NULL);
    sdl->window = NULL;
    sdl->renderer = NULL;
    sdl->map = map;
    sdl->quit = 1;
    ft_bzero(&(sdl->input), sizeof(t_input));
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        printf("Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return (NULL);
    }
    if (SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_RENDERER_ACCELERATED,
    &(sdl->window), &(sdl->renderer)) == -1)
        return (NULL);
    SDL_SetWindowTitle(sdl->window, WIN_NAME);
    SDL_SetWindowPosition(sdl->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    ft_bzero(&sdl->line, sizeof(t_ivec2) * WIN_W);
    t_uint32 rmask = 0x000000ff;
    t_uint32 gmask = 0x0000ff00;
    t_uint32 bmask = 0x00ff0000;
    t_uint32 amask = 0xff000000;
    sdl->surface = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, rmask, gmask, bmask, amask);
    sdl->texture = NULL;
    return (sdl);
}

void        destroy_sdl(t_sdl *sdl)
{
    if (sdl->window)
        SDL_DestroyWindow(sdl->window);
    if (sdl->renderer) 
        SDL_DestroyRenderer(sdl->renderer);
    free_map_struct(&(sdl->map));
    free(sdl->player);
    SDL_Quit();
}