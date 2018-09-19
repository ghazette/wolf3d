#ifndef WOLF3D_H
# define WOLF3D_H
#ifndef M_PI
# define M_PI 3.14159265359
#endif
# define DEGTORAD(DEG) ((DEG) * M_PI / 180.0)
# define LOGIC_STEP 150
# define ROT_LEFT 0x08
# define ROT_RIGHT 0x12
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# include "../libft/includes/libft.h"
# include "typedef.h"
# include <math.h>
# include <time.h>
# include "map.h"
# include <SDL2/SDL.h>
# define WIN_H 960
# define WIN_W 1440
# define WIN_H_HALF WIN_H / 2
# define LINESIZE WIN_W * 4
# define FOV 60
# define WIN_NAME "Wolf3D"
# define texWidth 64
# define texHeight 64
#include <stdio.h>

typedef struct      s_vec2
{
    double          x;
    double          y;
}                   t_vec2;

typedef struct      s_ivec2
{
    int             x;
    int             y;
}                   t_ivec2;

typedef struct      s_line
{
    int             start;
    int             end;
    double          walldist;
    double          lineheight;
    int             texX;
}                   t_line;

typedef struct      s_raycast
{
    double          camerax;
    int             hit;
    int             side;
    t_ivec2         step;
    t_ivec2         map;
    t_vec2          sidedist;
    t_vec2          raydir;
    t_vec2          deltadist;
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
    const t_uint8   *key;
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
    SDL_Window      *window;
    SDL_Event       event;
    SDL_Renderer    *renderer;
    SDL_Texture     *texture;
    SDL_Surface     *surface;
    t_line          line[WIN_W];
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
void                draw_line(int x, t_sdl *sdl, t_uint color);

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