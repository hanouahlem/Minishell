# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 19:25:19 by ahbey             #+#    #+#              #
#    Updated: 2024/09/18 15:18:03 by ahbey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
		parsing.c \

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror 

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) 

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re/