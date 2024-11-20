# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 17:05:23 by ahbey             #+#    #+#              #
#    Updated: 2024/09/04 15:26:45 by ahbey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  pipex.c\
		take_path.c\
		make_child.c\
		utils.c\
		free_all.c\

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

OBJS	=	$(SRCS:.c=.o)

NAME	=	pipex

LIBFT 	=	libft/libft.a

PRINTF  =   printf/libftprintf.a

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME) 

$(LIBFT):
	make -C libft
	
$(PRINTF):
	make -C printf

%.o: %.c pipex.h
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

.PHONY: all clean fclean re/