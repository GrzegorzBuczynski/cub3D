# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 22:56:26 by gbuczyns          #+#    #+#              #
#    Updated: 2024/11/10 18:03:17 by ssuchane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
CC = gcc
CFLAGS = -g -D DEBUG=1 #-Wall -Werror -Wextra 
RM = rm -f

SRCS =	main.c \
		handle_input.c \
		utils.c \
		init_map.c \
		display_server/init_display.c \
		check_map/check_map.c \
		check_map/check_player.c \
		check_map/check_borders.c \
		check_map/map_utils.c


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