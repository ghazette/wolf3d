#ifndef MAP_H
# define MAP_H
# define WOLF_HEADER "WOLF3D"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef unsigned int t_uint;

typedef struct  s_map
{
    char        title[17];
    int         width;
    int         height;
    int         size;
    char        **grid;
}               t_map;

t_map           *alloc_map_struct(void);
int             fill_map_grid(int fd, t_map *map);
void            set_title(char *title, t_map *map);
void            set_width(t_uint width, t_map *map);
void            set_height(t_uint height, t_map *map);
void            set_size(t_map *map);
void            free_map_struct(t_map **map);
void            print_struct(t_map *map);

#endif