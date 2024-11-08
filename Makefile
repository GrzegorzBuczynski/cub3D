# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 17:43:39 by ssuchane          #+#    #+#              #
#    Updated: 2024/11/08 16:38:32 by ssuchane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = gcc

# Compiler flags
WARNFLAGS = -Wall -Wextra -Werror
RLFLAG = -lm -g
CFLAGS = -g
HEADERS = -I./lib_ft -I./inc -I./minilibx
LDFLAGS = -L./lib_ft -l:libft.a -L./minilibx -lmlx $(RLFLAG)

# Source files
SRCS =	main.c \
		file.c \
		utils.c \
		src/check_map/check_map.c \
		src/check_map/check_player.c \
		src/check_map/check_borders.c 

OBJS = $(SRCS:.c=.o)

MINILIBX_REPO = https://github.com/42Paris/minilibx-linux.git
MINILIBX_DIR = minilibx
MINILIBX_LIB = $(MINILIBX_DIR)/libmlx.a

# Program Name
NAME = cub3D

# Libft src
LIBFT = ./lib_ft/libft.a

# Default rule
all: $(MINILIBX_DIR) $(MINILIBX_LIB) $(LIBFT) $(NAME)

$(MINILIBX_DIR):
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		git clone $(MINILIBX_REPO) $(MINILIBX_DIR); \
	fi

$(MINILIBX_LIB): | $(MINILIBX_DIR)
	@echo "Building MiniLibX library..."
	@$(MAKE) -C $(MINILIBX_DIR)

$(NAME): $(OBJS)
	@echo "Linking objects into executable..."
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(WARNFLAGS) $(CFLAGS) $(HEADERS) -c $< -o $@ 

# Make lib_ft
$(LIBFT):
	make -C lib_ft

# Clean up obj files
clean:
	make -C lib_ft clean
	make -C $(MINILIBX_DIR) clean
	rm -f $(OBJS)

# Full clean up
fclean: clean
	rm -f $(NAME)
	make -C lib_ft fclean
	rm -f $(MINILIBX_LIB)

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're', and 'bonus' are not interpreted as file names
.PHONY: all clean fclean re bonus

push:
	make fclean
	git add .
	git commit -m "make push!"
	git push