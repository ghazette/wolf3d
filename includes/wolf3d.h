#ifndef WOLF3D_H
# define WOLF3D_H
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# include "../libft/includes/libft.h"
# include <math.h>
# include "map.h"
# include "input.h"
# include "../minilibx/mlx.h"
# define WIN_H 960
# define WIN_W 1600
# define WIN_NAME "Wolf3D"
#ifndef M_PI
# define M_PI 3.14159265359
#endif
#define DEGTORAD(DEG)  (DEG * M_PI / 180)

typedef struct      s_vec2
{
    int             x;
    int             y;
}                   t_vec2;

typedef struct      s_player
{
    t_vec2          cellpos;
    t_vec2          incellpos;
    t_vec2          direction;
    double          angle;
    int             move;
}                   t_player;

typedef struct      s_mlx
{
    void            *ptr;
    void            *win;
    t_map           *map;
    int             bpp;
    int             line;
    int             ed;
    void            *img;
    char            *pixel_img;
    t_player        player;
}                   t_mlx;


t_mlx               *init_all_mlx(t_map *map);
int                 load_map_and_init_mlx(char *fn, t_mlx **mlx);

/*
** Drawing
*/

void                draw(t_mlx *mlx);
void                draw_point(int x, int y, t_mlx *mlx, t_uint color);


/*
** Hooks
*/

/*
int                 mouse_click_hook(int key, int x, int y, void *params);
int                 right_click_mouse_move_hook(int x, int y, void *param);
int                 mouse_release_hook(int key, int x, int y, void *param);
*/

/*
** Events
*/

void                exitprogram_evt(void *param);

/*
** load_map_evt (from load_map.c)
** function overflow ( > 5 )
** these functions are located in file load_map2.c
*/

int                 get_height(int fd, t_map *map);
int                 get_width(int fd, t_map *map);
int                 get_title(int fd, t_map *map);
void                error_and_free(int fd, t_map *map, char *msg);

#endif