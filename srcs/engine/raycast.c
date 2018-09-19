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

static void     store_line_to_draw(t_raycast *ray, t_player *player, t_line line[WIN_W], int x)
{
    if (ray->side == 0)
        line[x].walldist = (ray->map.x - player->pos.x + (1 - ray->step.x) / 2) / ray->raydir.x;
    else
        line[x].walldist = (ray->map.y - player->pos.y + (1 - ray->step.y) / 2) / ray->raydir.y;
    line[x].lineheight = (int)(WIN_H / line[x].walldist);
    line[x].start = -line[x].lineheight / 2 + WIN_H_HALF;
    if (line[x].start < 0)
        line[x].start = 0;
    line[x].end = line[x].lineheight / 2 + WIN_H_HALF;
    if (line[x].end >= WIN_H)
        line[x].end = WIN_H;
}

static void     get_texture_xy(t_raycast *ray, t_player *player, t_line line[WIN_W], int x)
{
    double wallX;
    if (ray->side == 0)
        wallX = player->pos.y + line[x].walldist * ray->raydir.y;
    else
        wallX = player->pos.x + line[x].walldist * ray->raydir.x;
    wallX -= floor((wallX));

    //x coordinate on the texture
    line[x].texX = (int)(wallX * (double)texWidth);
    if (ray->side == 0 && ray->raydir.x > 0)
        line[x].texX = texWidth - line[x].texX - 1;
    if (ray->side == 1 && ray->raydir.y < 0)
        line[x].texX = texWidth - line[x].texX - 1;
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
        get_texture_xy(&ray, sdl->player, sdl->line, x);
    }
}