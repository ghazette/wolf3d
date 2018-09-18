#include "../../includes/wolf3d.h"

int     get_title(int fd, t_map *map)
{
    char    buf[17];
    char    *title;
    int     size;
    int     err;
    int     i;

    err = 0;
    ft_bzero(buf, 17);
    size = read(fd, buf, 16);
    if (size < 16 || buf[0] == '\0')
        err++;
    i = ft_strlen(buf);
    while (i < size && err == 0)
        if (buf[i++] != '\0')
            err++;
    if (err || !(title = ft_strdup(buf)))
    {
        error_and_free(fd, map, "Wrong file format.\n");
        close(fd);
        return (0);
    }
    set_title(title, map);
    return (1);
}

int     get_width(int fd, t_map *map)
{
    unsigned char   buf[4];
    int             size;

    ft_bzero(buf, 4);
    size = read(fd, buf, 4);
    if (size < 4 || buf[3] == '\0' || (buf[0] != '\0' && buf[1] != '\0'))
    {
        error_and_free(fd, map, "Wrong file format.\n");
        return (0);
    }
    set_width((t_uint)((buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3]), map);
    if (map->width > 5000 || map->width <= 0)
    {
        error_and_free(fd, map, "Map is too small/large. (width/height >= 1 <= 5000)\n");
        return (0);
    }
    return (1);
}

int     get_height(int fd, t_map *map)
{
    unsigned char   buf[4];
    int             size;

    ft_bzero(buf, 4);
    size = read(fd, buf, 4);
    if (size < 4 || buf[3] == '\0' || (buf[0] != '\0' && buf[1] != '\0'))
    {
        error_and_free(fd, map, "Wrong file format.\n");
        return (0);
    }
    set_height((t_uint)((buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + buf[3]), map);
    if (map->height > 5000 || map->height <= 0)
    {
        error_and_free(fd, map, "Map is too small/large. (width/height >= 1 <= 5000)\n");
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