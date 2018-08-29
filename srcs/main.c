/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/24 16:31:59 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/24 18:50:42 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#define WIN_H 720
#define WIN_W 1280
#define WIN_NAME "Wolf3D"
#define FALSE 0
#define TRUE 1

typedef struct  s_world
{
    int         width;
    int         height;
    char        **map;
}               t_world;

typedef struct  s_vec2
{
    float       x;
    float       y;
}               t_vec2;

typedef struct  s_player
{
    t_vec2      pos;
    t_vec2      dir;
    t_vec2      plane;
    float       fov;
}               t_player;

int		wordcount(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
		{
			count++;
			while (!ft_isspace(str[i]) && str[i] != '\0')
				i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (count);
}

int     get_world_size(char *map_filename, t_world *world)
{
    char    *line;
    int     fd;
    
    line = NULL;
    fd = open(map_filename, O_RDONLY);
    get_next_line(fd, &line);
    if (!line)
        return (0);
    world->width = wordcount(line);
    world->height++;
    ft_strdel(&line);
    while (get_next_line(fd, &line) > 0)
    {
        world->height++;
        ft_strdel(&line);
    }   
    close(fd);
    if (world->height == 0 || world->width == 0)
        return (0);
    return (1);
}

int   set_world_map(t_world *world)
{
    int i;

    i = 0;
    if (!(world->map = (char**)malloc(sizeof(char*) * (world->height + 1))))
        return (0);
    if (!world->map)
        return (0);
    while (i < world->height)
    {
        if (!(world->map[i] = malloc(sizeof(char) * (world->width + 1))))
            return (0);
        i++;
    }
    world->map[i] = 0;
    return (1);
}

t_world *init_world(char *map_filename)
{
    char    *line;
    int     fd;
    t_world *world;

    if (!(world = malloc(sizeof(t_world))))
        return (NULL);
    world->width = 0;
    world->height = 0;
    world->map = NULL;
    if (!(get_world_size(map_filename, world)))
        return (NULL);
    if (!(set_world_map(world)))
        return (NULL);
    fd = open(map_filename, O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        ft_strdel(&line);
    }
    close(fd);
    return (world);
}


int main(int ac, char **av)
{
    void    *mlx;
    void    *win;
    t_world *world;

    world = init_world("map1");
    if (world)
        printf("width -> %d\nheight -> %d\n", world->width, world->height);
    mlx = mlx_init();
    win = mlx_new_window(mlx, WIN_W, WIN_H, WIN_NAME);

    mlx_loop(mlx);
    return (0);
}
