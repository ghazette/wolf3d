#include "../includes/wolf3d.h"

int main(int ac, char **av)
{
    t_mlx *mlx;

    if (ac < 2)
        return (0);
    if (!(load_map_and_init_mlx(av[1], &mlx)))
        return (0);
    print_struct(mlx->map);

    draw(mlx);
    //mlx_hook(mlx->win, 2, 1L, keyfunc, mlx);
    //mlx_mouse_hook(mlx->win, mouse_click_hook, mlx);
    //mlx_hook(mlx->win, 6, 1L << 10, right_click_mouse_move_hook, mlx); //right click hold
    
    //mlx_hook(mlx->win, 6, 1L << 6, mousemove, mlx); //mouse move
    //mlx_hook(mlx->win, 5, 1 << 3, mouse_release_hook, mlx); //mouse button release
    //mlx_string_put(mlx->ptr, mlx->win, 100, 100, 0xffffff, "0123456789");

    mlx_loop(mlx->ptr);
    return (0);
}


