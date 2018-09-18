#include "../../includes/wolf3d.h"

static void     set_variables(t_raycast *ray, t_player *player, int x)
{
    ray->camerax = 2 * x / (double)WIN_W - 1;
    ray->raydir.x = player->direction.x + player->plane.x * ray->camerax;
    ray->raydir.y = player->direction.y + player->plane.y * ray->camerax;

    ray->map.x = (int)player->pos.x;
    ray->map.y = (int)player->pos.y;

    ray->deltadist.x = fabs(1.0 / ray->raydir.x);
    ray->deltadist.y = fabs(1.0 / ray->raydir.y);
}

static void     set_raydir(t_raycast *ray, t_vec2 playerpos)
{
    if (ray->raydir.x < 0)
    {
        ray->step.x = -1;
        ray->sidedist.x = (playerpos.x - ray->map.x) * ray->deltadist.x;
    }
    else
    {
        ray->step.x = 1;
        ray->sidedist.x = (ray->map.x + 1.0 - playerpos.x) * ray->deltadist.x;
    }
    if (ray->raydir.y < 0)
    {
        ray->step.y = -1;
        ray->sidedist.y = (playerpos.y - ray->map.y) * ray->deltadist.y;
    }
    else
    {
        ray->step.y = 1;
        ray->sidedist.y = (ray->map.y + 1.0 - playerpos.y) * ray->deltadist.y;
    }
}

static void     get_nearest_wall(t_raycast *ray, int mapheight, int mapwidth, t_map *map)
{
    ray->hit = 0;
    while (ray->hit == 0)
    {
        if (ray->sidedist.x < ray->sidedist.y)
        {
            ray->sidedist.x += ray->deltadist.x;
            ray->map.x += ray->step.x;
            ray->side = 0;
        }
        else
        {
            ray->sidedist.y += ray->deltadist.y;
            ray->map.y += ray->step.y;
            ray->side = 1;
        }
        if ((ray->map.y >= 0 && ray->map.x < mapheight) && (ray->map.x >= 0 && ray->map.x < mapwidth))
            if (map->grid[ray->map.y][ray->map.x] > 0)
                ray->hit = 1;
    }
}

static void     store_line_to_draw(t_raycast *ray, t_player *player, t_ivec2 line[WIN_W], int x)
{
    int wallheight;

    if (ray->side == 0)
        ray->walldist = (ray->map.x - player->pos.x + (1 - ray->step.x) / 2) / ray->raydir.x;
    else
        ray->walldist = (ray->map.y - player->pos.y + (1 - ray->step.y) / 2) / ray->raydir.y;
    wallheight = (int)(WIN_H / ray->walldist);
    line[x].x = -wallheight / 2 + WIN_H_HALF;
    if (line[x].x < 0)
        line[x].x = 0;
    line[x].y = wallheight / 2 + WIN_H_HALF;
    if (line[x].y >= WIN_H)
        line[x].y = WIN_H;

}

void            raycast(t_sdl *sdl)
{
    t_raycast   ray;
    int         x;

    x = -1;
    while (++x < WIN_W)
    {
        set_variables(&ray, sdl->player, x);
        set_raydir(&ray, sdl->player->pos);
        get_nearest_wall(&ray, sdl->map->height, sdl->map->width, sdl->map);
        store_line_to_draw(&ray, sdl->player, sdl->line, x);
    }
}

/*
    if (sdl->player->pos.x < 1)
        sdl->player->pos.x = 1;
    if (sdl->player->pos.x >= sdl->map->width - 1)
        sdl->player->pos.x = sdl->map->width - 2;

    if (sdl->player->pos.y >= sdl->map->height - 1)
        sdl->player->pos.y = sdl->map->height -2;
    if (sdl->player->pos.y < 1)
        sdl->player->pos.y = 1;

*/