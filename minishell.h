
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

# define SQUOTE '\''
# define DQUOTE '"'
# define W_SPACE ' '
# define W_TAB '\t'

typedef struct t_env
{
	char			*key;
	char			*value;
	char			*content;
	struct t_env	*next;
}					t_env;

typedef struct t_token
{
	int				index;
	int				type;
	char			*value_t;
	struct t_token	*next;
	struct t_token	*prev;
}					t_token;


typedef struct t_mini
{
	char			*data;
	t_token			*token;
	t_env			*env;
}					t_mini;

typedef enum t_token_type
{
	REDIR_IN,      // <
	REDIR_OUT,     // >
	DBL_REDIR_IN,  // <<
	DBL_REDIR_OUT, // >>
	PIPE,          //|
	WORD,
}					t_token_type;

int					ft_check_redir_in_out(char *str);
int					ft_quote(char *str);

t_env				*ft_lstnew_env(void *content);
t_env				*ft_lstlast_env(t_env *lst);
void				ft_lstadd_back_env(t_env **lst, t_env *new);

t_token				*ft_lstnew_tok(void *values);
t_token				*add_prev(t_token *new);
void				ft_lstadd_back_tok(t_token **lst, t_token *new);
void				split_line(int i, char *line, t_token *tokenis);

t_env				*get_env(char **env);
char				*find_key_for_env(char *my_env);
char				*find_value_for_env(char *my_env);
int					ft_strlen_stop(char *str, char c);

int					ft_strcmp(const char *s1, const char *s2);
char				*token_negation(char *str);

char				*delete_quote(char *str);

char    *ft_get_key(char *str, t_mini *data);
#endif