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

    
    t_uint32    *pixels;

    t_uint32 i = 0;
    SDL_LockSurface(sdl->surface);
    //SDL_memset(sdl->surface->pixels, 0, sdl->surface->h * sdl->surface->pitch);
    for (int x = 0; x < WIN_W; x++)
    {
        int r,g,b,a;
        r = 0xd6; g = 0xcb; b = 0xc8, a = 0xff;

        //t_uint32 c = (r & 0xff) + ((g & 0xff) << 8) + ((b & 0xff) << 16) + ((a & 0xff) << 24);
        t_uint32 h = sdl->line[x].y - sdl->line[x].x;
        t_uint32 c = ((int)(r * (h / (double)WIN_H)) & 0xff) + (((int)(g * (h / (double)WIN_H)) & 0xff) << 8) + (((int)(b * (h / (double)WIN_H)) & 0xff) << 16) + (((int)(a * (h / (double)WIN_H)) & 0xff) << 24);
    //	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
        draw_line(x, sdl, c);
    }
    SDL_UnlockSurface(sdl->surface);
    sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface);
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

void        draw_line(int x, t_sdl *sdl, t_uint color)
{
    t_int32 i;
    t_uint32 *pixels;

    i = -1;
    pixels = (t_uint32*)sdl->surface->pixels;
    while (++i < sdl->line[x].x)
        pixels[(i * sdl->surface->w + x)] = 0xffff8877;
    while (sdl->line[x].x < sdl->line[x].y)
    {
        pixels[(sdl->line[x].x * sdl->surface->w + x)] = color;
        sdl->line[x].x++;
    }
    while (sdl->line[x].y < WIN_H)
    {
        pixels[(sdl->line[x].y * sdl->surface->w + x)] = 0xff444444;
        sdl->line[x].y++;
    }
}