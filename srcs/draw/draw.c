#include "../../includes/wolf3d.h"

void        draw(t_sdl *sdl)
{
    draw_point(sdl->player->pos.x, sdl->player->pos.y, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x+1, sdl->player->pos.y, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x-1, sdl->player->pos.y, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x, sdl->player->pos.y+1, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x+1, sdl->player->pos.y+1, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x-1, sdl->player->pos.y+1, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x + sdl->player->direction.x, sdl->player->pos.y + sdl->player->direction.y, sdl, 0x00FF00);

    
    int         pitch;
    uint32_t         *pixels;
    SDL_LockTexture(sdl->texture, NULL, (void**)&pixels, &pitch);
    for (int x = 0; x < WIN_W; x++)
        draw_line(x, sdl, pixels, 0xff0000);
    SDL_UnlockTexture(sdl->texture);
}

void        draw_point(int x, int y, t_sdl *sdl, t_uint color)
{
    if ((x >= 0 && x < WIN_W) && (y >= 0 && y < WIN_H))
    {
        SDL_SetRenderDrawColor(sdl->renderer, (color >> 16) & 0xff,
                                            (color >> 8) & 0xff,
                                            color & 0xff,
                                            (color >> 24) & 0xff);
        SDL_RenderDrawPoint(sdl->renderer, x, y);
    }
}

void        draw_line(int x, t_sdl *sdl, uint32_t *pixels, t_uint color)
{
    int pixel = sdl->line[x].x * WIN_W + x;
   /* SDL_SetRenderDrawColor(sdl->renderer, 
    */
   //printf("%d\n", pixel);
    while (sdl->line[x].x < sdl->line[x].y)
    {
        if ((x < 0 || x > WIN_W) || (sdl->line[x].x < 0 || sdl->line[x].y > WIN_H))
            break;
        pixels[pixel] = 0xff;
        pixel += WIN_W;
        sdl->line[x].x++;
    }
}