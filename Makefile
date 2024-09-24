# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 19:25:19 by ahbey             #+#    #+#              #
#    Updated: 2024/09/24 14:58:15 by ahbey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
		parsing.c \
		utils.c  \

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror 

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

LIBFT 	=	libft/libft.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) 

$(LIBFT):
	make -C libft

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
		rm -f ${OBJS}
		make -C libft clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean

re:		fclean all

.PHONY: all clean fclean re/