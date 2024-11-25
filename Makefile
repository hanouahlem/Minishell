# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 15:10:46 by manbengh          #+#    #+#              #
#    Updated: 2024/11/25 15:10:47 by manbengh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
		parsing.c \
		get_path.c \
		free_all.c \
		utils.c  \
		tokenise/token.c  \
		tokenise/create_token.c \
		tokenise/token_check.c  \
		tokenise/organise_token.c \
		tokenise/organise_utils.c \
		expand/expand.c \
		expand/expand_utils.c  \
		expand/expand_utils_2.c \
		bultins/built_in.c \
		bultins/ft_exit.c \
		bultins/unset_export.c \
		bultins/ft_echo.c \
		prints.c \
		exec/ft_exec.c  \
		# tokenise/pour_test_malloc.c\
		
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
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=supp.txt ./minishell

.PHONY: all clean fclean re/