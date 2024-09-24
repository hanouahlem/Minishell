# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 19:25:19 by ahbey             #+#    #+#              #
#    Updated: 2024/09/24 14:57:55 by manbengh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
	parsing.c \
	utils.c  \

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror 

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

INC = -Iincludes -I/usr/include -ILibft

LIBFT = Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(INC) -lreadline -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C Libft

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

clean:
	rm -f ${OBJ}
	make -C Libft clean

fclean: clean
	rm -f ${NAME}
	make -C Libft fclean

re: fclean all

.PHONY: all clean fclean re