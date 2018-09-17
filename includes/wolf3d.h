#ifndef WOLF3D_H
# define WOLF3D_H
#ifndef M_PI
# define M_PI 3.14159265359
#endif
# define DEGTORAD(DEG) ((DEG) * M_PI / 180.0)
# define CELLSIZE 64
# define HORIZONTAL 0x02
# define VERTICAL 0x04
# define NOHIT -1
# define LOGIC_STEP 150
# define ROT_LEFT 0x08
# define ROT_RIGHT 0x12
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# include "../libft/includes/libft.h"
# include <math.h>
# include <time.h>
# include "map.h"
# include <SDL2/SDL.h>
# define WIN_H 640
# define WIN_W 1500
# define WIN_NAME "Wolf3D"

#include <stdio.h>
typedef struct SDL_Window t_sdl_window;
typedef union SDL_Event t_sdl_event;
typedef struct SDL_Renderer t_sdl_renderer;
typedef struct timespec t_timespec;
typedef unsigned char t_uchar;

typedef struct      s_vec2
{
    double          x;
    double          y;
}                   t_vec2;

typedef struct      s_raycast
{
    t_vec2          cella;
    t_vec2          cellb;
    int             stepxa;
    int             stepya;
    int             stepxb;
    int             stepyb;
    int             ya;
    int             xa;
    int             yb;
    int             xb;
    int             stopa;
    int             stopb;
}                   t_raycast;

typedef struct      s_player
{
    t_vec2          pos;
    t_vec2          direction;
    t_vec2          plane;
    t_vec2          direction_strafe;
    double          velocity_move;
    double          velocity_angle;
    double          angle;
    int             move;
}                   t_player;

typedef struct      s_input
{
    const t_uchar   *key;
    int             mousex;
    int             mousey;
    int             mousexrel;
    int             mouseyrel;
}                   t_input;

typedef struct      s_sdl_loop
{
    clock_t         current_time;
    clock_t         new_time;
    double          frametime;
    double          dt;
    double          accumulator;
}                   t_sdl_loop;

typedef struct      s_sdl
{
    t_sdl_window    *window;
    t_sdl_event     event;
    t_sdl_renderer  *renderer;
    t_map           *map;
    t_player        *player;
    int             quit;
    t_input         input;
}                   t_sdl;


t_sdl               *init_sdl(t_map *map);
void                destroy_sdl(t_sdl *sdl);
int                 load_map_and_init_sdl(char *fn, t_sdl **sdl);
void                start_loop(int enableshowfps, t_sdl *sdl);

/*
** Drawing
*/
void                draw(t_sdl *sdl);
void                draw_point(int x, int y, t_sdl *sdl, t_uint color);
void                draw_line(int x, int y[2], t_sdl *sdl, t_uint color);

/*
** Engine
*/

void                raycast(t_sdl *sdl);

/*
** Player
*/

t_player            *init_player(t_map *map, int startx, int starty);
void                rotate_player(t_sdl *sdl, double dt, int type);
void                move_player(t_sdl *sdl, double dt);

/*
** Events
*/

void                exitprogram_evt(t_sdl *sdl);

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