
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
#include "libft/libft.h"

typedef struct mini_s
{
	char			*data;
	struct mini_s	*next;
}				mini_t;

typedef enum token_type
{
	W_SPACE,
}		token_type;

typedef struct s_token
{
	int	index;
	char	*str;
	token_type	tokens;
	struct s_token *next;
	struct s_token *prev;
}		t_token;

typedef struct env_s
{
	char			*key;
	char			*value;
	char			*content;
	char			*node_env;
	char			**new_env;
	struct env_s	*next;
}					env_t;

// int					ft_strlen(char *str);
int					ft_fleche(char *str);
int					ft_quote(char *str);

env_t	*ft_lstnew_env(void *content);
env_t	*ft_lstlast_env(env_t *lst);
void	ft_lstadd_back_env(env_t **lst, env_t *new);

void get_env(char **env);

#endif