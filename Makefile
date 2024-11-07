# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 17:43:39 by ssuchane          #+#    #+#              #
#    Updated: 2024/11/07 20:19:37 by ssuchane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = gcc

# Compiler flags
WARNFLAGS = -Wall -Wextra -Werror
RLFLAG = -lm -g
CFLAGS = -g
HEADERS = -I./lib_ft -I./inc
LDFLAGS = -L./lib_ft -l:libft.a $(RLFLAG)

# Source files
SRCS =	main.c \
		file.c \
		# src/check_map/check_map.c \
		# src/check_map/check_player.c \
		# src/check_map/check_borders.c 

OBJS = $(SRCS:.c=.o)

# Program Name
NAME = cub3D

# Libft src
LIBFT = ./lib_ft/libft.a

# Default rule
all: $(LIBFT) $(NAME)
	
#$(LIBFT) $(NAME)
$(NAME): $(OBJS)
#	clear
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
	rm -f $(OBJS)

# Full clean up
fclean: clean
	rm -f $(NAME)
	make -C lib_ft fclean

# Rebuild
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're', and 'bonus' are not interpreted as file names
.PHONY: all clean fclean re bonus

push:
	make fclean
	git add .
	git commit -m "make push!"
	git push