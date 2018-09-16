NAME = wolf3d

OS = $(shell uname)

#--------ROOT srcs--------#

ROOT_PATH = ./srcs/

ROOT_NAME = main.c mlx.c

#--------EVENTS---------#

EVT_PATH = ./srcs/event/

EVT_NAME = exit_program.c

#----------DRAW---------#

DRAW_PATH = ./srcs/draw/

DRAW_NAME = draw.c

#----------MAP----------#

MAP_PATH = ./srcs/map/

MAP_NAME = map_memory.c map_setters.c load_map.c load_map2.c

#----------ENGINE-------#

ENGINE_PATH = ./srcs/engine/

ENGINE_NAME = init_engine.c raycast.c

#--------OBJECTS--------#

OBJ_PATH = ./objs/

OBJ_DRAW = $(addprefix $(OBJ_PATH)draw/, $(DRAW_NAME))

OBJ_EVT = $(addprefix $(OBJ_PATH)event/, $(EVT_NAME))

OBJ_MAP = $(addprefix $(OBJ_PATH)map/, $(MAP_NAME))

OBJ_ENGINE = $(addprefix $(OBJ_PATH)engine/, $(ENGINE_NAME))

OBJ_ROOT = $(addprefix $(OBJ_PATH), $(ROOT_NAME))

OBJ_LIST += $(OBJ_DRAW)

OBJ_LIST += $(OBJ_EVT)

OBJ_LIST += $(OBJ_MAP)

OBJ_LIST += $(OBJ_ROOT)

OBJ_LIST += $(OBJ_ENGINE)

OBJ = $(OBJ_LIST:%.c=%.o)

INC =	./includes/wolf3d.h\
		./includes/map.h\
		./includes/input.h

LIBFT_PATH = ./libft/libft.a

MLX_PATH = ./minilibx/libmlx.a

MLX_PATH_LINUX = ./minilibx_linux/libmlx_Linux.a

CC = gcc

FLAGS = -O3 -g

all: $(NAME)

ifeq ($(OS), Darwin)
$(NAME): $(OBJ) $(LIBFT_PATH) $(MLX_PATH)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_PATH) $(MLX_PATH) -o $(NAME) -framework OpenGl -framework AppKit
endif

ifeq ($(OS), Linux)
$(NAME): $(OBJ) $(LIBFT_PATH) $(MLX_PATH_LINUX)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_PATH) $(MLX_PATH_LINUX) $(INC) -o $(NAME) -lm -lSDL2
endif

$(OBJ_PATH)%.o: $(ROOT_PATH)%.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)draw/%.o: $(DRAW_PATH)%.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)event/%.o: $(EVT_PATH)%.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)map/%.o: $(MAP_PATH)%.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)engine/%.o: $(ENGINE_PATH)%.c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_PATH):
	make -C ./libft/

$(MLX_PATH):
	make -C ./minilibx/

$(MLX_PATH_LINUX):
	make -C ./minilibx_linux/

clean:
	rm -f $(OBJ)
	make -C ./libft/ clean
	make -C ./minilibx/ clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft/ fclean

re: fclean all

.PHONY: all clean fclean re