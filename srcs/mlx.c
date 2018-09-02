#include "../includes/wolf3d.h"

t_mlx       *init_all_mlx(t_map *map)
{
    t_mlx *mlx;

    if (!(mlx = malloc(sizeof(t_mlx))))
        return (NULL);
    mlx->ptr = mlx_init();
    mlx->win = mlx_new_window(mlx->ptr, WIN_W, WIN_H, WIN_NAME);
    mlx->map = map;
    mlx->img = NULL;
    return (mlx);
}

