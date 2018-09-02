#include "../../includes/wolf3d.h"

void    exitprogram_evt(void *param)
{
    t_mlx *mlx;

    mlx = (t_mlx*)param;
    if (mlx->img)
        mlx_destroy_image(mlx->ptr, mlx->img);
    mlx_clear_window(mlx->ptr, mlx->win);
    mlx_destroy_window(mlx->ptr, mlx->win);
    free_map_struct(&(mlx->map));
    free(mlx);
    mlx = NULL;
    exit(0);
}