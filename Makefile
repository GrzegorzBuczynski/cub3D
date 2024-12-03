# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 22:56:26 by gbuczyns          #+#    #+#              #
#    Updated: 2024/12/03 15:24:46 by gbuczyns         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
CC = gcc
CFLAGS = -g -D DEBUG=1 #-Wall -Werror -Wextra 
RM = rm -f

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
		map/map.c \
		map/minimap.c \
		math/math_utils.c \
		rendering/colors.c \
		rendering/walls.c \
		rendering/draw.c \
		rendering/render.c \
		rendering/textures.c \
		utils/time.c \
		utils/utils.c 


SRCS_DIR = src/
SRCS_PATHS = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS_PATHS:.c=.o)

INCLUDES_DIR = includes
MINILIBX_DIR = lib/minilibx
CFLAGS += -I$(INCLUDES_DIR) -I$(MINILIBX_DIR)

LIBRARY_DIRS = lib/lib_ft $(MINILIBX_DIR)
LIBRARY_DIRSC = lib/lib_ft
LIBRARY = mlx ft X11 Xext m
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

%.o: %.c
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