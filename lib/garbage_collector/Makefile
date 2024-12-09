# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 19:42:53 by gbuczyns          #+#    #+#              #
#    Updated: 2024/12/09 20:07:48 by gbuczyns         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS :=	ft_lstadd_back.c \
		ft_lstnew.c \
		garbage_colector.c \
		gc_free.c \
		gc_std_functions.c 

OBJS := $(SRCS:.c=.o)

NAME = libgc.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all