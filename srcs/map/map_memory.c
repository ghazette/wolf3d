#include "../../includes/wolf3d.h"

t_map   *alloc_map_struct(void)
{
    t_map *map;

    if (!(map = malloc(sizeof(t_map))))
        return (NULL);
    map->grid = NULL;
    return (map);
}

static int free_map_struct_backward(t_map **map, int n)
{
    if (map)
    {
        while (--n)
        {
            free((*map)->grid[n]);
            (*map)->grid[n] = NULL;
        }
        free((*map)->grid[n]);
        (*map)->grid[n] = NULL;
        free((*map)->grid);
        (*map)->grid = NULL;
        free(*map);
        *map = NULL;
    }
}

int  fill_map_grid(int fd, t_map *map)
{
    int     i;
    int     j;
    char    *buf;

    i = 0;
    if (!(buf = malloc(sizeof(char) * (map->width))))
        return (0);
    if (!(map->grid = (char**)malloc(sizeof(char*) * (map->height + 1))))
        return (0);
    while (i < map->height)
    {
        if (!(map->grid[i] = malloc(sizeof(char) * (map->width))))
            return (0);
        if (read(fd, buf, map->width) < map->width)
        {
            ft_printf(KRED"Wrong file format.\n"KNRM);
            free_map_struct_backward(&map, i);
            return (0);
        }
        j = -1;
        while (++j < map->width)
            map->grid[i][j] = buf[j];
        i++;
    }
    map->grid[i] = 0;
    return (1);
}

void    free_map_struct(t_map **map)
{
    if (*map)
    {
        if ((*map)->grid)
            ft_free2d(&((*map)->grid));
        free(*map);
        *map = NULL;
    }
}
