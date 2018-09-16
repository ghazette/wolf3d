#include "../../includes/wolf3d.h"

static double is_blocking_cell(t_raycast *ray, t_map *map, double type)
{
    double y;
    double x;

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
    if (map->grid[(int)y][(int)x] > 0)
        return (1);
    return (0);
}

static void get_ya(t_sdl *sdl, t_raycast *ray)
{
    double coeff;

    coeff = -1;
    if (sdl->player->view.angle == 0 || sdl->player->view.angle == 180)
    {
        ray->stopa = 1;
        return;
    }
    if (sdl->player->view.angle > 0 && sdl->player->view.angle < 180)
        coeff = CELLSIZE;
    ray->ya = floor(sdl->player->pos.y / CELLSIZE) * CELLSIZE + coeff;
    ray->cella.y = ray->ya / CELLSIZE;
    if (coeff == CELLSIZE)
        ray->stepya = CELLSIZE;
    else
        ray->stepya = -CELLSIZE;
}

static void get_xa(t_sdl *sdl, t_raycast *ray, double relangle)
{
    double angle_computed;

    angle_computed = tan(DEGTORAD(relangle));
    ray->xa = sdl->player->pos.x + (sdl->player->pos.y - ray->ya) / angle_computed;
    ray->stepxa = CELLSIZE / angle_computed;
    ray->cella.x = ray->xa / CELLSIZE;
    if (sdl->player->view.angle > 0 && sdl->player->view.angle < 180)
        ray->stepxa = -ray->stepxa;
}

static void get_yb(t_sdl *sdl, t_raycast *ray, double relangle)
{
    double angle_computed;

    angle_computed = tan(DEGTORAD(relangle));
    ray->yb = sdl->player->pos.y + (sdl->player->pos.x - ray->xb) * angle_computed;
    ray->stepyb = CELLSIZE * angle_computed;
    ray->cellb.y = ray->yb / CELLSIZE;
    if ((sdl->player->view.angle > 0 && sdl->player->view.angle < 90) || (sdl->player->view.angle > 270 && sdl->player->view.angle < 360))
        ray->stepyb = -ray->stepyb;

}

static void get_xb(t_sdl *sdl, t_raycast *ray)
{
    double coeff;

    coeff = CELLSIZE;
    if (sdl->player->view.angle == 90 || sdl->player->view.angle == 270)
    {
        ray->stopb = 1;
        return;
    }
    if (sdl->player->view.angle > 90 && sdl->player->view.angle < 270)
        coeff = -1;
    ray->xb = floor(sdl->player->pos.x / CELLSIZE) * CELLSIZE + coeff;
    ray->cellb.x = ray->xb / CELLSIZE;
    if (coeff == CELLSIZE) 
        ray->stepxb = CELLSIZE;
    else
        ray->stepxb = -CELLSIZE;
}

static double   raycast_set_angle(double angle)
{
    /*
    if (angle > 0 && angle < 90)
        return (angle);
    else if (angle > 270 && angle < 360)
        return (360.0 - angle);
    else if (angle > 90 && angle < 180)
        return (180.0 - angle);
    return (angle);
    */
    if (angle > 0 && angle < 90)
        angle -= 90;
    else if (angle > 270 && angle < 360)
        angle -= 360.0;
    else if (angle > 90 && angle < 180)
        angle -= 180.0;
    if (angle < 0)
        angle = -angle;
    return (angle);
}

static double   raycast_vertical(t_sdl *sdl, t_raycast *ray, double angle)
{
    double i;

    i = 0;
    while (!is_blocking_cell(ray, sdl->map, VERTICAL) && i < 30)
    {
        if (ray->stopb)
            break;
        ray->xb += ray->stepxb;
        ray->yb += ray->stepyb;
        ray->cellb.x = ray->xb / CELLSIZE;
        ray->cellb.y = ray->yb / CELLSIZE;
        i++;
    }
    return (fabs(sdl->player->pos.y - ray->yb) / sin(DEGTORAD(angle)));
}

static double   raycast_horizontal(t_sdl *sdl, t_raycast *ray, double angle)
{
    double i;

    i = 0;
    while (!is_blocking_cell(ray, sdl->map, HORIZONTAL) && i < 30)
    {
        if (ray->stopa)
            break ;
        ray->xa += ray->stepxa;
        ray->ya += ray->stepya;
        ray->cella.x = ray->xa / CELLSIZE;
        ray->cella.y = ray->ya / CELLSIZE;
        i++;
    }
    return (fabs(sdl->player->pos.y - ray->ya) / sin(DEGTORAD(angle)));
}

void        raycast(t_sdl *sdl)
{
    t_raycast ray;
    double         p0 = 0, p1 = 0;
    double         i;
    double      angle;
    double      save = sdl->player->view.angle;

    clock_t startc,endc;
    double  exectime;

    startc = clock();
    double testangle = 30;
    angle = sdl->player->view.angle - (sdl->player->view.fov / 2);

    if (angle < 0)
        angle += 360;
        for (int j = 640; j < 640 + 320; j++)
    {
        int yy[2];
        yy[0] = WIN_H / 2;
        yy[1] = WIN_H;
        draw_line(j, yy, sdl, 0xCCCCCA);
    }
    while (i < sdl->player->view.projectionplane)
    {
        sdl->player->view.angle = angle;
        ft_bzero(&ray, sizeof(ray));
        get_ya(sdl, &ray);
        get_xa(sdl, &ray, fabs(testangle));
        get_xb(sdl, &ray);
        get_yb(sdl, &ray, fabs(testangle));
        double angleb = raycast_set_angle(sdl->player->view.angle);
        p0 = raycast_horizontal(sdl, &ray, fabs(testangle));
        p1 = raycast_vertical(sdl, &ray, fabs(testangle));
        if (p0 < p1 || ray.stopb)
        {
                draw_point(ray.xa, ray.ya, sdl, 0xFF00CC);
                draw_point(ray.xa + 1, ray.ya, sdl, 0xFF00CC);
                draw_point(ray.xa, ray.ya + 1, sdl, 0xFF00CC);
                draw_point(ray.xa + 1, ray.ya + 1, sdl, 0xFF00CC);
                double wallh = ((CELLSIZE / p0) * sdl->player->view.planedist);
                int center = WIN_H / 2;
                int y[2];
                y[0] = center - (wallh / 2);
                y[1] = center + (wallh / 2);
                if (y[0] < 0)
                    y[0] = 0;
                if (y[1] > WIN_H)
                    y[1] = WIN_H;
                draw_line(i + 640, y, sdl, 0x00FF00);
            //printf("cell hit [%d][%d]\n", ray.cella.y, ray.cella.x);
        }
        else
        {
            draw_point(ray.xb, ray.yb, sdl, 0xFF00CC);
            draw_point(ray.xb + 1, ray.yb, sdl, 0xFF00CC);
            draw_point(ray.xb, ray.yb + 1, sdl, 0xFF00CC);
            draw_point(ray.xb + 1, ray.yb + 1, sdl, 0xFF00CC);
            //printf("cell hit [%d][%d]\n", ray.cellb.y, ray.cellb.x);
            double wallh = ((CELLSIZE / p1) * sdl->player->view.planedist);
            int center = WIN_H / 2;
            int y[] = {center - (wallh / 2), center + (wallh / 2)};
            if (y[0] < 0)
                y[0] = 0;
            if (y[1] > WIN_H)
                y[1] = WIN_H;
            draw_line(i + 640, y, sdl, 0x00FF00);
        }
        angle += sdl->player->view.rayangle;
        
        if (testangle > 0)
            testangle -= sdl->player->view.rayangle;
        else
            testangle += sdl->player->view.rayangle;
        if (angle >= 360)
            angle -= 360;
        i++;
    }
    sdl->player->view.angle = save;
    endc = clock();
    exectime= (double)(endc-startc) / CLOCKS_PER_SEC;
    //printf("Execution time for raycasting %f seconds.\n", exectime);
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