#include "../../includes/wolf3d.h"

void raycast(t_sdl *sdl)
{
    if (sdl->player->pos.x < 1)
        sdl->player->pos.x = 1;
    if (sdl->player->pos.x >= sdl->map->width - 1)
        sdl->player->pos.x = sdl->map->width - 2;

    if (sdl->player->pos.y >= sdl->map->height - 1)
        sdl->player->pos.y = sdl->map->height -2;
    if (sdl->player->pos.y < 1)
        sdl->player->pos.y = 1;
    for (int x = 0; x < WIN_W; x++)
    {
        double cameraX = 2 * x / (double)WIN_W - 1;
        double rayDirX = sdl->player->direction.x + sdl->player->plane.x * cameraX;
        double rayDirY = sdl->player->direction.y + sdl->player->plane.y * cameraX;

        int mapX = (int)sdl->player->pos.x;
        int mapY = (int)sdl->player->pos.y;

        double sideDistX;
        double sideDistY;
        
        double deltaDistX = fabs(1.0 / rayDirX);
        double deltaDistY = fabs(1.0 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (sdl->player->pos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - sdl->player->pos.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (sdl->player->pos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - sdl->player->pos.y) * deltaDistY;
        }
        while (hit == 0)
        {
                        //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if ((mapY >= 0 && mapX < sdl->map->height) && (mapX >= 0 && mapX < sdl->map->width))
                if (sdl->map->grid[mapY][mapX] > 0)
                    hit = 1;
        }
        if (side == 0)
            perpWallDist = (mapX - sdl->player->pos.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - sdl->player->pos.y + (1 - stepY) / 2) / rayDirY;
        
      //Calculate height of line to draw on screen
      int lineHeight = (int)(WIN_H / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + WIN_H / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + WIN_H / 2;
      if(drawEnd >= WIN_H)drawEnd = WIN_H - 1;
      int y[] = {drawStart, drawEnd};
      draw_line(x, y, sdl, 0x0FF000);
    }
}