#include "../../includes/wolf3d.h"

static void draw_grid(t_sdl *sdl)
{
 
    int i = 0;
    int j;
    int k;
    int y[2];

    while (sdl->map->grid[i] != 0)
    {
        j = 0;
        while (j < sdl->map->width)
        {
            if (sdl->map->grid[i][j] >= 1)
            {
                k = 0;
                y[0] = (i * CELLSIZE);
                y[1] = y[0] + CELLSIZE;
                while (k < CELLSIZE)
                {
                    draw_line((j * CELLSIZE) + k, y, sdl, 0x00AACD);
                    k++;
                }
            }
            j++;
        }
        i++;
    }
}

static void draw_ray(t_sdl *sdl)
{
    int x;
    int y;
    int i = 0;
    double viewangle = sdl->player->view.angle + (sdl->player->view.fov / 2);
    double angle;
    
    while (i < sdl->player->view.projectionplane)
    {
        angle = DEGTORAD(viewangle);
        x = 100 * cos(angle);
        y = 100 * sin(angle);
        viewangle -= sdl->player->view.rayangle;
        draw_point(sdl->player->pos.x + x, sdl->player->pos.y + y, sdl, 0xFF0000);
        i++;
    }

}


void        draw(t_sdl *sdl)
{
    /*draw_point(sdl->player->pos.x, sdl->player->pos.y, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x+1, sdl->player->pos.y, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x-1, sdl->player->pos.y, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x, sdl->player->pos.y+1, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x+1, sdl->player->pos.y+1, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x-1, sdl->player->pos.y+1, sdl, 0xFFFFFF);
    draw_point(sdl->player->pos.x + sdl->player->direction.x, sdl->player->pos.y + sdl->player->direction.y, sdl, 0x00FF00);

    draw_grid(sdl);
    draw_ray(sdl);*/

    raycast(sdl);
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

void        draw_line(int x, int y[2], t_sdl *sdl, t_uint color)
{
    int y0;


    y0 = y[0];
    SDL_SetRenderDrawColor(sdl->renderer, (color >> 16) & 0xff,
                                        (color >> 8) & 0xff,
                                        color & 0xff,
                                        (color >> 24) & 0xff);
    while (y0 < y[1])
    {
        if ((x < 0 || x > WIN_W) || (y0 < 0 || y0 > WIN_H))
            break;
        SDL_RenderDrawPoint(sdl->renderer, x, y0);
        y0++;
    }
}