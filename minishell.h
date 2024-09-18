
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct mini_s
{
	char data;
	struct mini_s *next;
}			mini_t;

int	ft_quote(char *str);

#endif