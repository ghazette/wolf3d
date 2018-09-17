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
    double  x;
    double  y;
    double  sinus;
    double  cosi;
    double  angle;
    
    //reset_vec_player(sdl);
    /*if (type == ROT_LEFT)
    {
        sdl->player->angle -= sdl->player->velocity_angle * dt;
        if (sdl->player->angle < 0)
            sdl->player->angle = 358;
    }
    if (type == ROT_RIGHT)
    {
        sdl->player->angle += sdl->player->velocity_angle * dt;
        if (sdl->player->angle > 360)
            sdl->player->angle = 0;
    }*/
    if (type == ROT_RIGHT)
    {
        /*
    double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        */
       double olddirx = sdl->player->direction.x;
       double oldplanex = sdl->player->plane.x;
    sdl->player->angle = DEGTORAD(50) * dt;
    sdl->player->direction.x = sdl->player->direction.x * cos(-sdl->player->angle) - sdl->player->direction.y * sin(-sdl->player->angle);
    sdl->player->direction.y = olddirx * sin(-sdl->player->angle) + sdl->player->direction.y * cos(-sdl->player->angle);
    sdl->player->plane.x = sdl->player->plane.x * cos(-sdl->player->angle) - sdl->player->plane.y * sin(-sdl->player->angle);
    sdl->player->plane.y = oldplanex * sin(-sdl->player->angle) + sdl->player->plane.y * cos(-sdl->player->angle);
    }
    /*
    angle = DEGTORAD(sdl->player->view.angle);
    sinus = sin(angle);
    cosi = cos(angle);
    x = sdl->player->direction.x * cosi + sdl->player->direction.y * (-sinus);
    y = sdl->player->direction.x * sinus + sdl->player->direction.y * cosi;
    sdl->player->direction.x = x;
    sdl->player->direction.y = y;
    */
}

void            move_player(t_sdl *sdl, double dt)
{
    sdl->player->pos.x += sdl->player->direction.x * sdl->player->velocity_move * dt;
    sdl->player->pos.y += sdl->player->direction.y * sdl->player->velocity_move * dt;
}