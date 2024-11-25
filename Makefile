# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 19:25:19 by ahbey             #+#    #+#              #
#    Updated: 2024/11/25 17:02:28 by ahbey            ###   ########.fr        #
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
		exec_hanou/ft_exec_hm.c \
		exec_hanou/ft_path.c \
		# exec/ft_exec.c \

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

LIBFT 	=	libft/libft.a

PRINTF  =   printf/libftprintf.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -lreadline -o $(NAME)  -g3

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C printf

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
		rm -f ${OBJS}
		make -C libft clean
		make -C printf clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean
		make -C printf fclean

re:		fclean all

leak: all
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=supp.txt ./minishell

.PHONY: all clean fclean re/