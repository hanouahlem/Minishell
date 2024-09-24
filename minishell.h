
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// pour les utiliser apres plus lisible
// enum		token_type
// {
// 	REDIR_IN = '>',
// 	REDIR_OUT = '<',
// 	PIPE = '|',
// 	SPACE_ = ' ',
// 	WORD,
// };

typedef struct mini_s
{
	char data;
	struct mini_s *next;
}			mini_t;

int     ft_strlen(char *str);
int	ft_fleche(char *str);
int	ft_quote(char *str);

#endif