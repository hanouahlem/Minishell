# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 16:26:36 by ahbey             #+#    #+#              #
#    Updated: 2023/12/19 16:57:55 by ahbey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putnbr_x.c

CC	=	cc 

CFLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

NAME		= libftprintf.a

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
