#include "../../includes/wolf3d.h"

static double   clamp_angle(double angle)
{
    if (angle > 90.0 && angle < 180.0)
        return (angle - 90.0);
    if (angle > 180.0 && angle < 270.0)
        return (angle - 180.0);
    if (angle > 270.0 && angle < 360.0)
        return (angle - 270.0);
    return angle;
}

static double is_blocking_cell(t_raycast *ray, t_map *map, double type)
{
    int y;
    int x;

    if (type == HORIZONTAL)
    {
        x = ray->cella.x;
        y = ray->cella.y;
    }
    if (type == VERTICAL)
    {
        x = ray->cellb.x;
        y = ray->cellb.y;
    }
    if (x < 0 || x >= map->width)
        return (0);
    if (y < 0 || y >= map->height)
        return (0);
    if (map->grid[y][x] > 0)
        return (1);
    return (0);
}

static void get_ya(t_sdl *sdl, t_raycast *ray, double angle)
{
    if (angle >= 0.00 && angle <= 180.00)
    {
        ray->ya = (int)sdl->player->pos.y / CELLSIZE * CELLSIZE + CELLSIZE;
        ray->cella.y = ray->ya / CELLSIZE;
        ray->stepya = CELLSIZE;
    }
    else
    {
        ray->ya = (int)sdl->player->pos.y / CELLSIZE * CELLSIZE - 1;
        ray->cella.y = ray->ya / CELLSIZE;
        ray->stepya = -CELLSIZE;
    }
}

static void get_xa(t_sdl *sdl, t_raycast *ray, double angle)
{
    double angle_computed;

    angle_computed = tan(DEGTORAD(360 - angle));
    ray->xa = (int)sdl->player->pos.x + ((int)sdl->player->pos.y - ray->ya) / angle_computed;
    ray->stepxa = CELLSIZE / angle_computed;
    ray->cella.x = ray->xa / CELLSIZE;
    if (angle > 0.0 && angle < 180.0)
        ray->stepxa = -ray->stepxa;
}

static void get_yb(t_sdl *sdl, t_raycast *ray, double angle)
{
    double angle_computed;

    angle_computed = tan(DEGTORAD(360 - angle));
    ray->yb = (int)sdl->player->pos.y + ((int)sdl->player->pos.x - ray->xb) * angle_computed;
    ray->stepyb = CELLSIZE * angle_computed;
    ray->cellb.y = ray->yb / CELLSIZE;
    if ((angle > 0.0 && angle < 90.0) || (angle > 270.0 && angle < 360.0))
        ray->stepyb = -ray->stepyb;
}

static void get_xb(t_sdl *sdl, t_raycast *ray, double angle)
{
    if (angle >= 90.00 && angle <= 270.00)
    {
        ray->xb = (int)sdl->player->pos.x / CELLSIZE * CELLSIZE - 1;
        ray->cellb.x = ray->xb / CELLSIZE;
        ray->stepxb = -CELLSIZE;
    }
    else
    {
        ray->xb = (int)sdl->player->pos.x / CELLSIZE * CELLSIZE + CELLSIZE;
        ray->cellb.x = ray->xb / CELLSIZE;
        ray->stepxb = CELLSIZE;
    }
}

static double   raycast_vertical(t_sdl *sdl, t_raycast *ray, double angle)
{
    double i;

    i = 0;
    while (!is_blocking_cell(ray, sdl->map, VERTICAL) && i < 30)
    {
        ray->xb += ray->stepxb;
        ray->yb += ray->stepyb;
        ray->cellb.x = ray->xb / CELLSIZE;
        ray->cellb.y = ray->yb / CELLSIZE;
        i++;
    }
    return (fabs((int)(sdl->player->pos.x - ray->xb) / cos(DEGTORAD(angle))));
}

static double   raycast_horizontal(t_sdl *sdl, t_raycast *ray, double angle)
{
    double i;

    i = 0;
    while (!is_blocking_cell(ray, sdl->map, HORIZONTAL) && i < 30)
    {

        ray->xa += ray->stepxa;
        ray->ya += ray->stepya;
        ray->cella.x = ray->xa / CELLSIZE;
        ray->cella.y = ray->ya / CELLSIZE;
        i++;
    }
    return (fabs((int)(sdl->player->pos.y - ray->ya) / sin(DEGTORAD(angle))));
}

void        raycast(t_sdl *sdl)
{
    t_raycast   ray;
    double      p[2];
    double      angle;
    double wallh;
    ft_bzero(&ray, sizeof(t_raycast));
    angle = (sdl->player->view.fov / 2) + sdl->player->view.angle;
    if (angle > 360)
        angle -= 360;
        double angleb = -30;
            for (int j = 640; j < 640 + 320; j++)
    {
        int yy[2];
        yy[0] = WIN_H / 2;
        yy[1] = WIN_H;
        draw_line(j, yy, sdl, 0xCCCCCA);
    }
    //printf("angle : %f\n", sdl->player->view.angle);
    int i = 0; 
    for (int i = 0; i < (int)sdl->player->view.projectionplane; i++)
    {
        get_ya(sdl, &ray, angle);
        get_xa(sdl, &ray, angle);
        get_xb(sdl, &ray, angle);
        get_yb(sdl, &ray, angle);
        //printf("angle %f\n", angle);
        p[0] = raycast_horizontal(sdl, &ray, angle);
        p[1] = raycast_vertical(sdl, &ray, angle);
        //if (p[1] + 0.01 > p[0])
          //  printf("equal p0 %f /// p1 %f\n", p[0], p[1]);
        if (p[0] < p[1])
        {
            draw_point(ray.xa, ray.ya, sdl, 0xFFFFFF);
            draw_point(ray.xa + 1, ray.ya, sdl, 0xFFFFFF);
            draw_point(ray.xa, ray.ya + 1, sdl, 0xFFFFFF);
            draw_point(ray.xa + 1, ray.ya + 1, sdl, 0xFFFFFF);
                p[0] *= cos(DEGTORAD(angleb));
                wallh = (CELLSIZE / p[0]) * sdl->player->view.planedist ;

                int center = WIN_H / 2;
                int y[2];
                y[0] = center - (wallh / 2);
                y[1] = center + (wallh / 2);
                if (y[0] < 0)
                    y[0] = 0;
                if (y[1] > WIN_H)
                    y[1] = WIN_H;
                draw_line(i + 640, y, sdl, 0x0FF000);
            //printf("cell hit [%d][%d]\n", ray.cella.y, ray.cella.x);
        }
        else
        {
            draw_point(ray.xb, ray.yb, sdl, 0xFF00CC);
            draw_point(ray.xb + 1, ray.yb, sdl, 0xFF00CC);
            draw_point(ray.xb, ray.yb + 1, sdl, 0xFF00CC);
            draw_point(ray.xb + 1, ray.yb + 1, sdl, 0xFF00CC);
            //printf("cell hit [%d][%d]\n", ray.cellb.y, ray.cellb.x);
            p[1] *= cos(DEGTORAD(angleb));
            wallh = (CELLSIZE / p[1]) * sdl->player->view.planedist;
            int center = WIN_H / 2;
            int y[] = {center - (wallh / 2), center + (wallh / 2)};
            if (y[0] < 0)
                y[0] = 0;
            if (y[1] > WIN_H)
                y[1] = WIN_H;
            draw_line(i + 640, y, sdl, 0x0FF000);
        }
        angle -= sdl->player->view.rayangle;
        angleb += sdl->player->view.rayangle;
        if (angle >= 360)
            angle -= 360;
        if (angle <= 0)
            angle += 360.00;
    }
    
}

/*
static double      is_in_map(t_raycast *ray, t_map *map, double type)
{
    if (type == VERTICAL)
        if ((ray->cellb.x >= 0 && ray->cellb.x < map->width) && (ray->cellb.y >= 0 && ray->cellb.y < map->height))
            return (1);
    if (type == HORIZONTAL)
        if ((ray->cella.x >= 0 && ray->cella.x < map->width) && (ray->cella.y >= 0 && ray->cella.y < map->height))
            return (1);
    return (0);
}
*/