#include "../../includes/wolf3d.h"

void    set_title(char *title, t_map *map)
{
    ft_bzero(map->title, 16);
    ft_strcpy(map->title, title);
    ft_strdel(&title);
}

void    set_width(t_uint width, t_map *map)
{
    if (width > 5000)
        width = 5000;
    map->width = width;
}

void    set_height(t_uint height, t_map *map)
{
    if (height > 5000)
        height = 5000;
    map->height = height;
}

void    set_size(t_map *map)
{
    map->size = map->width * map->height;
}
