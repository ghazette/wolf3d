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
  //generate some textures
    t_uint32    texture[8][64 * 64];

  for(int v = 0; v < texWidth; v++)
  for(int y = 0; y < texHeight; y++)
  {
    int xorcolor = (v * 256 / texWidth) ^ (y * 256 / texHeight);
    //int xcolor = x * 256 / texWidth;
    int ycolor = y * 256 / texHeight;
    int xycolor = y * 128 / texHeight + x * 128 / texWidth;
    texture[0][texWidth * y + v] = 65536 * 254 * (v != y && v != texWidth - y); //flat red texture with black cross
    texture[1][texWidth * y + v] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
    texture[2][texWidth * y + v] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
    texture[3][texWidth * y + v] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
    texture[4][texWidth * y + v] = 256 * xorcolor; //xor green
    texture[5][texWidth * y + v] = 65536 * 192 * (x % 16 && y % 16); //red bricks
    texture[6][texWidth * y + v] = 65536 * ycolor; //red gradient
    texture[7][texWidth * y + v] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
  }
    while (++i < sdl->line[x].start)
        pixels[(i * sdl->surface->w + x)] = 0xffff8877;
    while (sdl->line[x].start < sdl->line[x].end)
    {
        color = 0xff0000ff;
        int d = sdl->line[x].start * 256 - WIN_H * 128 + sdl->line[x].lineheight * 128;  //256 and 128 factors to avoid floats
        // TODO: avoid the division to speed this up
        int texY = ((d * sdl->line[x].lineheight) / sdl->line[x].lineheight) / 256;
       //printf("%d\n", texHeight * texY + sdl->line[x].texX);
       //exit(0);
        if (texHeight * texY + sdl->line[x].texX < 4096)
            color = 0x000000ff + texture[2][texHeight * texY + sdl->line[x].texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
       // if  (side == 1) color = (color >> 1) & 8355711;
        pixels[(sdl->line[x].start * sdl->surface->w + x)] = color;
        sdl->line[x].start++;
    }
    while (sdl->line[x].end < WIN_H)
    {
        pixels[(sdl->line[x].end * sdl->surface->w + x)] = 0xff444444;
        sdl->line[x].end++;
    }
}