#include "../../includes/wolf3d.h"

static int  open_file(char *fn)
{
    int fd;

    if ((fd = open(fn, O_RDONLY)) < 0)
    {
        error_and_free(fd, NULL, "That file doesn't exist.\n");
        return (0);
    }
    return (fd);
}

static int  check_header(int fd)
{
    char buf[7];

    read(fd, buf, 6);
    buf[6] = '\0';
    if (!ft_strcmp(WOLF_HEADER, buf))
        return (1);
    error_and_free(fd, NULL, "Wrong file format.\n");
    return (0);
}

int        load_map_and_init_mlx(char *fn, t_mlx **mlx)
{
    t_map   *map;
    int     fd;

    if (!(fd = open_file(fn)))
        return (0);
    if (!check_header(fd))
        return (0);
    if (!(map = alloc_map_struct()))
        return (0);
    if (!(get_title(fd, map)))
        return (0);
    if (!(get_width(fd, map)))
        return (0);
    if (!(get_height(fd, map)))
        return (0);
    set_size(map);
    if (!(fill_map_grid(fd, map)))
        return (0);
    if (!(*mlx = init_all_mlx(map)))
        return (0);
    close(fd);
    return (1);
}

/*
** DEBUG FUNC
*/

void    print_struct(t_map *map)
{
    ft_printf("header: %s\ntitle: %s\nwidth: %d\nheight: %d\nsize: %d\n", WOLF_HEADER, map->title, map->width, map->height, map->size);
    int i, j;
    i = 0;
    if (map->grid)
        while (i < map->height)
        {
            j = 0;
            while (j < map->width)
            {
                ft_printf("%d", map->grid[i][j]);
                j++;
            }
            ft_printf("\n");
            i++;
        }
}
