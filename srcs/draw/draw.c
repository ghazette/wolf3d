#include "../../includes/wolf3d.h"

void        draw(t_mlx *mlx)
{
    if (mlx->img)
        mlx_destroy_image(mlx->ptr, mlx->img);
    if (!(mlx->img = mlx_new_image(mlx->ptr, WIN_W, WIN_H)))
        return;
    mlx->pixel_img = mlx_get_data_addr(mlx->img,
    &mlx->bpp, &mlx->line, &mlx->ed);

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