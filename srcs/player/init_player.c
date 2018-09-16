#include "../../includes/wolf3d.h"

t_player *init_player(t_map *map, int startx, int starty)
{
    t_player *p;

    if (!(p = malloc(sizeof(t_player))))
        return (NULL);
    p->move = 0;
    p->view.fov = 60.0;
    p->view.angle = 0.0;
    p->view.projectionplane = 320.0;
    p->view.planedist = (p->view.projectionplane / 2) / tan((p->view.fov / 2) * M_PI / 180);
    p->pos.x = startx;
    p->pos.y = starty;
    p->view.rayangle = p->view.fov / p->view.projectionplane;
    p->direction.x = 1;
    p->direction.y = 0;
    p->direction_strafe.x = 0;
    p->direction_strafe.y = 1;
    p->velocity_move = 150;
    p->velocity_angle = 120;
    return (p);
}