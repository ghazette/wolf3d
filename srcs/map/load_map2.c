#include "../../includes/wolf3d.h"

int     get_title(int fd, t_map *map)
{
    char    buf[17];
    char    *title;

    ft_bzero(buf, 17);
    read(fd, buf, 16);
    if (buf[0] == '\0')
    {
        error_and_free(fd, map, "Wrong file format.\n");
        return (0);
    }
    if (!(title = ft_strdup(buf)))
    {
        close(fd);
        return (0);
    }
    set_title(title, map);
    return (1);
}

int     get_width(int fd, t_map *map)
{
    unsigned char   buf[4];

    ft_bzero(buf, 4);
    read(fd, buf, 4);
    if (buf[3] == '\0')
    {
        error_and_free(fd, map, "Wrong file format.\n");
        return (0);
    }
    set_width((t_uint)((buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3]), map);
    if (map->width > 5000)
    {
        error_and_free(fd, map, "Map is too large. (width/height > 5000)\n");
        return (0);
    }
    return (1);
}

int     get_height(int fd, t_map *map)
{
    unsigned char   buf[4];

    ft_bzero(buf, 4);
    read(fd, buf, 4);
    if (buf[3] == '\0')
    {
        error_and_free(fd, map, "Wrong file format.\n");
        return (0);
    }
    set_height((t_uint)((buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3]), map);
    if (map->height > 5000)
    {
        error_and_free(fd, map, "Map is too large. (width/height > 5000)\n");
        return (0);
    }
    return (1);
}

void    error_and_free(int fd, t_map *map, char *msg)
{
    if (msg)
        ft_printf(KRED"%s"KNRM, msg);
    free_map_struct(&map);
    close(fd);
}