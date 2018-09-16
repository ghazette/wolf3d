#include "../includes/wolf3d.h"

/*
int     keyfunc(int key, void *param)
{
    t_mlx *mlx;

    mlx = (t_mlx*)param;

    if (key == LEFT_ARROW)
    {
        mlx->player->view.angle -= 2;
        if (mlx->player->view.angle < 0)
            mlx->player->view.angle = 358;
        draw(mlx);
    }
    if (key == RIGHT_ARROW)
    {
        mlx->player->view.angle += 2;
        if (mlx->player->view.angle >= 360)
            mlx->player->view.angle = 0;
        draw(mlx);
    }
    if (key == UP_ARROW)
    {
        mlx->player->move = 1;
        draw(mlx);
    }
   // printf("Angle : %f\n", mlx->player->view.angle);
}
*/

int main(int ac, char **av)
{
    t_sdl *sdl;
    if (ac < 2)
        return (0);
    if (!(load_map_and_init_sdl(av[1], &sdl)))
        return (0);
    sdl->player = init_player(sdl->map, 86.959738, 320.122207);
    start_loop(0, sdl);
    return (0);
}


