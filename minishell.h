
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

typedef struct mini_s
{
	char			*data;
	struct mini_s	*next;
}					mini_t;

typedef struct env_s
{
	char			**take_env;
	struct env_s	*next;
}					env_t;

int					ft_strlen(char *str);
int					ft_fleche(char *str);
int					ft_quote(char *str);

#endif