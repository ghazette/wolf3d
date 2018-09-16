#include "../../includes/wolf3d.h"

static void    reset_vec_player(t_sdl *sdl)
{
    sdl->player->direction.x = 1;
    sdl->player->direction.y = 0;
    sdl->player->direction_strafe.x = 0;
    sdl->player->direction_strafe.y = 1;
}

void            rotate_player(t_sdl *sdl, double dt, int type)
{
    double  x;
    double  y;
    double  sinus;
    double  cosi;
    double  angle;
    
    reset_vec_player(sdl);
    if (type == ROT_LEFT)
    {
        sdl->player->view.angle -= sdl->player->velocity_angle * dt;
        if (sdl->player->view.angle < 0)
            sdl->player->view.angle = 358;
    }
    if (type == ROT_RIGHT)
    {
        sdl->player->view.angle += sdl->player->velocity_angle * dt;
        if (sdl->player->view.angle > 360)
            sdl->player->view.angle = 0;
    }
    angle = DEGTORAD(sdl->player->view.angle);
    sinus = sin(angle);
    cosi = cos(angle);
    x = sdl->player->direction.x * cosi + sdl->player->direction.y * (-sinus);
    y = sdl->player->direction.x * sinus + sdl->player->direction.y * cosi;
    sdl->player->direction.x = x;
    sdl->player->direction.y = y;
}

void            move_player(t_sdl *sdl, double dt)
{
    sdl->player->pos.x += sdl->player->direction.x * sdl->player->velocity_move * dt;
    sdl->player->pos.y += sdl->player->direction.y * sdl->player->velocity_move * dt;
}