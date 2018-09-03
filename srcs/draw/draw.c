#include "../../includes/wolf3d.h"

static int is_cell(int x, int y, t_map *map)
{
    int i;
    int j;

    i = x / 64;
    j = y / 64;
    if (map->grid[j][i] > 0)
        return (1);
    return (0);
}

static void rotate(t_mlx *mlx)
{
    int x;
    int y;
    double angle;
    
    angle = DEGTORAD(mlx->player.angle);
    x = mlx->player.direction.x * cos(angle) + mlx->player.direction.y * (-sin(angle));
    y = mlx->player.direction.x * sin(angle) + mlx->player.direction.y * cos(angle);
    mlx->player.direction.x = x;
    mlx->player.direction.y = y;
}

static void move(t_mlx *mlx)
{
    if (mlx->player.move)
    {
        mlx->player.cellpos.x += mlx->player.direction.x;
        mlx->player.cellpos.y += mlx->player.direction.y;
    }
}

void        raycasting(t_mlx *mlx)
{
    int cellsize;

    cellsize = 16;
    rotate(mlx);
    move(mlx);
    draw_point(mlx->player.cellpos.x, mlx->player.cellpos.y, mlx, 0xFFFFFF);
    draw_point(mlx->player.cellpos.x+1, mlx->player.cellpos.y, mlx, 0xFFFFFF);
    draw_point(mlx->player.cellpos.x-1, mlx->player.cellpos.y, mlx, 0xFFFFFF);
    draw_point(mlx->player.cellpos.x, mlx->player.cellpos.y+1, mlx, 0xFFFFFF);
    draw_point(mlx->player.cellpos.x+1, mlx->player.cellpos.y+1, mlx, 0xFFFFFF);
    draw_point(mlx->player.cellpos.x-1, mlx->player.cellpos.y+1, mlx, 0xFFFFFF);
    draw_point(mlx->player.cellpos.x + mlx->player.direction.x, mlx->player.cellpos.y + mlx->player.direction.y, mlx, 0xFF0000);
    mlx->player.move = 0;
    mlx->player.direction.x = 10;
    mlx->player.direction.y = 0;
}

void        draw(t_mlx *mlx)
{
    if (mlx->img)
        mlx_destroy_image(mlx->ptr, mlx->img);
    if (!(mlx->img = mlx_new_image(mlx->ptr, WIN_W, WIN_H)))
        return;
    mlx->pixel_img = mlx_get_data_addr(mlx->img,
    &mlx->bpp, &mlx->line, &mlx->ed);
    raycasting(mlx);
    //draw routine
    mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}

static int  conv_coord(int x, int y, t_mlx *mlx)
{
    return ((x * ((mlx->bpp) / 8)) + (y * mlx->line));
}

void        draw_point(int x, int y, t_mlx *mlx, t_uint color)
{
    int pixel_pos;

    pixel_pos = conv_coord(x, y, mlx);
    if (pixel_pos < (WIN_W * WIN_H * (mlx->bpp / 8)) && pixel_pos >= 0)
    {
        if (color != 0)
        {
            mlx->pixel_img[pixel_pos] = (char)(color & 0xff);
            mlx->pixel_img[pixel_pos + 1] = (char)((color >> 8) & 0xff);
            mlx->pixel_img[pixel_pos + 2] = (char)((color >> 16) & 0xff);
        }
        else
        {
            mlx->pixel_img[pixel_pos] = (char)0;
            mlx->pixel_img[pixel_pos + 1] = (char)0;
            mlx->pixel_img[pixel_pos + 2] = (char)0;
        }
    }
}