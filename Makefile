# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 19:25:19 by ahbey             #+#    #+#              #
#    Updated: 2024/10/03 16:57:46 by manbengh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
		parsing.c \
		utils.c  \
		get_path.c \
		token.c  \
		create_token.c \
		token_check.c  \

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror 

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

LIBFT 	=	libft/libft.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME) 

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

leak: all
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=supp.txt  ./minishell

.PHONY: all clean fclean re/