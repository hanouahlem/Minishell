
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

typedef struct mini_s
{
	char			*data;
	struct mini_s	*next;
}				mini_t;

typedef enum token_type
{
	REDIR_IN,      // <
	REDIR_OUT,     // >
	DBL_REDIR_IN,  // <<
	DBL_REDIR_OUT, // >>
	PIPE,          //|
	WORD,
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
	struct env_s	*next;
}					env_t;

typedef enum token_type
{
	REDIR_IN,      // <
	REDIR_OUT,     // >
	DBL_REDIR_IN,  // <<
	DBL_REDIR_OUT, // >>
	PIPE,          //|
	WORD,
	W_SPACE,
}					token_type;

typedef struct s_token
{
	int				index;
	int				type;
	char			*value_t;
	// token_type		tokens;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

int					ft_check_redir_in_out(char *str);
int					ft_quote(char *str);

env_t				*ft_lstnew_env(void *content);
env_t				*ft_lstlast_env(env_t *lst);
void				ft_lstadd_back_env(env_t **lst, env_t *new);

t_token				*ft_lstnew_tok(void *values);
void				ft_lstadd_back_tok(t_token **lst, t_token *new);
void	split_line(char *line, t_token *tokenis);

void				get_env(char **env);
char	*find_key_for_env(char *my_env);
char	*find_value_for_env(char *my_env);
int	ft_strlen_stop(char *str, char c);

int					ft_strcmp(const char *s1, const char *s2);






#endif