# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 19:25:19 by ahbey             #+#    #+#              #
#    Updated: 2024/10/07 21:44:58 by ahbey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
		parsing.c \
		get_path.c \
		utils.c  \
		token.c  \
		create_token.c \
		token_check.c  \
		expand.c \
		retirerquote.c \
		ce_que_moha_a_supp.c \
		
CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

LIBFT 	=	libft/libft.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)  -g3

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