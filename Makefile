# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 22:56:26 by gbuczyns          #+#    #+#              #
#    Updated: 2024/12/09 20:14:47 by ssuchane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -g -D DEBUG=1 #-Wall -Werror -Wextra 
RM = rm -f

HEADERS = includes/color.h \
		includes/cub3d.h \
		includes/error_message.h \
		includes/key_linux.h \
		includes/structs.h \
		includes/key_events.h 
		

SRCS =	main.c \
		compass.c \
		raycaster_utils.c \
		controls/close_window.c \
		controls/controls.c \
		controls/mouse_controls.c \
		controls/movement.c \
		controls/rotate_game.c \
		display_server/init_display.c \
		display_server/mlx_safe.c \
		init/handle_input.c \
		init/init_player.c \
		init/init_textures_wraper.c \
		init/textures_init.c \
		map/check_borders.c \
		map/check_map.c \
		map/check_player.c \
		map/init_map.c \
		map/map_utils.c \
		map/minimap.c \
		map/minimap_utils.c \
		math/math_utils.c \
		rendering/colors.c \
		rendering/walls.c \
		rendering/setup_walls.c \
		rendering/draw.c \
		rendering/draw_line.c \
		rendering/main_background.c \
		rendering/render.c \
		rendering/textures.c \
		utils/time.c \
		utils/utils.c 


SRCS_DIR = src/
SRCS_PATHS = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS_PATHS:.c=.o)

INCLUDES_DIR = includes
MINILIBX_DIR = lib/minilibx
GARBAGE_COLLECTOR_DIR = lib/garbage_collector
CFLAGS += -I$(INCLUDES_DIR) -I$(MINILIBX_DIR) -I$(GARBAGE_COLLECTOR_DIR)

LIBRARY_DIRS = lib/lib_ft $(MINILIBX_DIR) $(GARBAGE_COLLECTOR_DIR)
LIBRARY_DIRSC = lib/lib_ft $(GARBAGE_COLLECTOR_DIR)
LIBRARY = mlx ft gc X11 Xext m
LDFLAGS = $(addprefix -L, $(LIBRARY_DIRS)) $(addprefix -l, $(LIBRARY))

MINILIBX_REPO = https://github.com/42Paris/minilibx-linux.git
MINILIBX_DIR = lib/minilibx

all: $(MINILIBX_DIR) $(LIBRARY) $(NAME)
bonus: all

$(MINILIBX_DIR):
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		git clone $(MINILIBX_REPO) $(MINILIBX_DIR); \
	fi

$(LIBRARY):
	@$(foreach dir, $(LIBRARY_DIRS), $(MAKE) -C $(dir);)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@$(foreach dir, $(LIBRARY_DIRSC), $(MAKE) -C $(dir) clean;)

fclean: clean
	$(RM) $(NAME)
	@$(foreach dir, $(LIBRARY_DIRSC), $(MAKE) -C $(dir) fclean;)
	rm -rf lib/minilibx

re: fclean all

.PHONY: all clean fclean re $(MINILIBX_DIR)

push:
	make fclean
	git add .
	git commit -m "make push!"
	git push

rerun: 
	make re
	clear
	./cub3D map.cub
	
run: all
	clear
	./cub3D map.cub

run42: all
	clear
	./cub3D 42_map.cub