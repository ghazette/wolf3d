#include "../../includes/wolf3d.h"

t_player *init_player(t_map *map, int startx, int starty)
{
    t_player *p;

    if (!(p = malloc(sizeof(t_player))))
        return (NULL);
    p->move = 0;
    p->angle = DEGTORAD(50);
    p->pos.x = startx;
    p->pos.y = starty;
    p->direction.x = -1;
    p->direction.y = 0;
    p->plane.x = 0;
    p->plane.y = 0.66;
    p->direction_strafe.x = 0;
    p->direction_strafe.y = 1;
    p->velocity_move = 5;
    p->velocity_angle = 10;
    return (p);
}