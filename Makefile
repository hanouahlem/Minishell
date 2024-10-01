# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 19:25:19 by ahbey             #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/09/26 18:46:34 by ahbey            ###   ########.fr        #
=======
#    Updated: 2024/09/24 14:57:55 by manbengh         ###   ########.fr        #
>>>>>>> MANAAAAAR
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
<<<<<<< HEAD
		parsing.c \
		utils.c  \
		get_path.c \
		token.c  \
		create_token.c \
=======
	parsing.c \
	utils.c  \
>>>>>>> MANAAAAAR

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror 

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

<<<<<<< HEAD
LIBFT 	=	libft/libft.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME) 

$(LIBFT):
	make -C libft
=======
INC = -Iincludes -I/usr/include -ILibft

LIBFT = Libft/libft.a
>>>>>>> MANAAAAAR

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(INC) -lreadline -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C Libft

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

clean:
<<<<<<< HEAD
		rm -f ${OBJS}
		make -C libft clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean
=======
	rm -f ${OBJ}
	make -C Libft clean

fclean: clean
	rm -f ${NAME}
	make -C Libft fclean
>>>>>>> MANAAAAAR

re: fclean all

.PHONY: all clean fclean re