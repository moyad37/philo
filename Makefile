# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 12:00:15 by sgoffaux          #+#    #+#              #
#    Updated: 2023/03/08 14:12:47 by mmanssou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	cc
INCLUDE	=	includes
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE)
RM		=	rm -f

SRCS	=	philosophers.c \
			srcs/int_handler.c \
			srcs/fill.c \
			srcs/philo.c \
			srcs/threads.c

OBJS	=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -pthread  $(OBJS) -o $(NAME)

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			@$(RM) $(OBJS)
			
fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
