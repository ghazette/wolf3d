#include "../../includes/wolf3d.h"

static t_uint32       apply_shadow(t_sdl *sdl, int x, t_int32 r, t_int32 g, t_int32 b, double dist)
{
    double          coeff;
    double          r1, g1, b1;

    coeff = 1 - (sdl->line[x].walldist / dist);
    r1 = r / 3;
    g1 = g / 3;
    b1 = b / 3;
    r *= coeff;
    g *= coeff;
    b *= coeff;
    if (r <= r1)
        r = r1;
    if (g <= g1)
        g = g1;
    if (b <= b1)
        b = b1;
        return ((r & 0xff) + ((g & 0xff) << 8) + ((b & 0xff) << 16) + (0xff << 24));
}

void        draw(t_sdl *sdl)
{
   
    t_uint32    *pixels;

    t_uint32 i = 0;
    SDL_LockSurface(sdl->surface);
    for (int x = 0; x < WIN_W; x++)
    {
        int r,g,b,a;
        r = 0xff; g = 0xff; b = 0xff, a = 0xff;

        t_uint32 h = sdl->line[x].end - sdl->line[x].start;
        t_uint32 c = apply_shadow(sdl, x, 0x25, 0xcf, 0x9a, 23);
        draw_line(x, sdl, c);
    }
    SDL_UnlockSurface(sdl->surface);
    sdl->texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface);
}

void        draw_line(int x, t_sdl *sdl, t_uint color)
{
    t_int32 i;
    t_uint32 *pixels;

    i = -1;
    pixels = (t_uint32*)sdl->surface->pixels;
    while (++i < sdl->line[x].start)
        pixels[(i * sdl->surface->w + x)] = 0xffff8877;
    while (sdl->line[x].start < sdl->line[x].end)
    {
        pixels[(sdl->line[x].start * sdl->surface->w + x)] = color;
        sdl->line[x].start++;
    }
    while (sdl->line[x].end < WIN_H)
    {
        pixels[(sdl->line[x].end * sdl->surface->w + x)] = 0xff444444;
        sdl->line[x].end++;
    }
}