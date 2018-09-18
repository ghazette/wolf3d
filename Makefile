NAME = wolf3d

OS = $(shell uname)

#--------ROOT srcs--------#

ROOT_PATH = ./srcs/

ROOT_NAME = main.c

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

ENGINE_NAME = raycast.c sdl.c sdl_loop.c

#-----------PLAYER------#

PLAYER_PATH = ./srcs/player/

PLAYER_NAME = init_player.c player_move.c

#--------OBJECTS--------#

OBJ_PATH = ./objs/

OBJ_DRAW = $(addprefix $(OBJ_PATH)draw/, $(DRAW_NAME))

OBJ_EVT = $(addprefix $(OBJ_PATH)event/, $(EVT_NAME))

OBJ_MAP = $(addprefix $(OBJ_PATH)map/, $(MAP_NAME))

OBJ_ENGINE = $(addprefix $(OBJ_PATH)engine/, $(ENGINE_NAME))

OBJ_PLAYER = $(addprefix $(OBJ_PATH)player/, $(PLAYER_NAME))

OBJ_ROOT = $(addprefix $(OBJ_PATH), $(ROOT_NAME))

OBJ_LIST += $(OBJ_DRAW)

OBJ_LIST += $(OBJ_EVT)

OBJ_LIST += $(OBJ_MAP)

OBJ_LIST += $(OBJ_ROOT)

OBJ_LIST += $(OBJ_ENGINE)

OBJ_LIST += $(OBJ_PLAYER)

OBJ = $(OBJ_LIST:%.c=%.o)

INC =	./includes/wolf3d.h\
		./includes/map.h\
		./includes/typedef.h

LIBFT_PATH = ./libft/libft.a

CC = gcc

FLAGS = -O3 -g


all: $(NAME)

ifeq ($(OS), Darwin)
$(NAME): $(OBJ) $(LIBFT_PATH) 
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_PATH) -o $(NAME) -framework SDL2
endif

ifeq ($(OS), Linux)
$(NAME): $(OBJ) $(LIBFT_PATH)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_PATH)  $(INC) -o $(NAME) -lm -lSDL2 -lpthread
endif

$(OBJ_PATH)%.o: $(ROOT_PATH)%.c $(INC)
	-mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)draw/%.o: $(DRAW_PATH)%.c $(INC)
	-mkdir -p $(OBJ_PATH)draw/
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)event/%.o: $(EVT_PATH)%.c $(INC)
	-mkdir -p $(OBJ_PATH)event/
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)map/%.o: $(MAP_PATH)%.c $(INC)
	-mkdir -p $(OBJ_PATH)map/
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)engine/%.o: $(ENGINE_PATH)%.c $(INC)
	-mkdir -p $(OBJ_PATH)engine/
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH)player/%.o: $(PLAYER_PATH)%.c $(INC)
	-mkdir -p $(OBJ_PATH)player/
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_PATH):
	make -C ./libft/

clean:
	rm -f $(OBJ)
	make -C ./libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft/ fclean

re: fclean all

.PHONY: all clean fclean re