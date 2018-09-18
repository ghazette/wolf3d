#include "../../includes/wolf3d.h"

static void    reset_vec_player(t_sdl *sdl)
{
    sdl->player->direction.x = -1;
    sdl->player->direction.y = 0;
    sdl->player->direction_strafe.x = 0;
    sdl->player->direction_strafe.y = 1;
}

void            rotate_player(t_sdl *sdl, double dt, int type)
{
    double  olddirx;
    double  oldplanex;
    double  sinus[2];
    double  cosi[2];
    double  angle;

    angle = DEGTORAD(sdl->player->velocity_angle) * dt;
    cosi[0] = cos(-angle);
    sinus[0] = sin(-angle);
    cosi[1] = cos(angle);
    sinus[1] = sin(angle);
    olddirx = sdl->player->direction.x;
    oldplanex = sdl->player->plane.x;
    if (type == ROT_RIGHT)
    {
        sdl->player->direction.x = sdl->player->direction.x * cosi[0] - sdl->player->direction.y * sinus[0];
        sdl->player->direction.y = olddirx * sinus[0] + sdl->player->direction.y * cosi[0];
        sdl->player->plane.x = sdl->player->plane.x * cosi[0] - sdl->player->plane.y * sinus[0];
        sdl->player->plane.y = oldplanex * sinus[0] + sdl->player->plane.y * cosi[0];
    }
    if (type == ROT_LEFT)
    {
        sdl->player->direction.x = sdl->player->direction.x * cosi[1] - sdl->player->direction.y * sinus[1];
        sdl->player->direction.y = olddirx * sinus[1] + sdl->player->direction.y * cosi[1];
        sdl->player->plane.x = sdl->player->plane.x * cosi[1] - sdl->player->plane.y * sinus[1];
        sdl->player->plane.y = oldplanex * sinus[1] + sdl->player->plane.y * cosi[1];
    }
}

void            move_player(t_sdl *sdl, double dt)
{
    sdl->player->pos.x += sdl->player->direction.x * sdl->player->velocity_move * dt;
    sdl->player->pos.y += sdl->player->direction.y * sdl->player->velocity_move * dt;
}