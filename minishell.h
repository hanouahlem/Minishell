/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:39:23 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/07 19:19:49 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Colors.h"
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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

typedef struct s_expand
{
	char			*str;
	int				i;
	int				i_len;
	char			*new_str;
	int				n;
	int				n_len;
	struct t_mini	*data;
}					t_expand;

typedef struct t_token
{
	int				index;
	int				type;
	char			*value_t;
	struct t_token	*next;
	struct t_token	*prev;
}					t_token;

typedef struct s_parse
{
	char			*cmd;
	char			**args;
	int				*typefile;
	char			**filename;
	int				argslen;
	int				typelen;
	int				args_count;
	int				typefile_count;
	int				filename_count;
	int				size_cmd;
	int				fd;
	pid_t			pid;
}					t_parse;

typedef struct t_exec
{
	int				nbcmd;
	char			**cmds;
	int				*pid;
	int				pipe_fd[2];
	int				pipe_prev;
	char			**env_exec;
	char			*path;
}					t_exec;

typedef struct t_hdoc
{
	int				pipe_fd[2];
	char			*delim;
}					t_hdoc;

typedef struct t_mini
{
	int				exit_status;
	int				nbr_hd;
	t_token			*token;
	t_env			*env;
	t_expand		*expand;
	t_parse			*parser;
	t_exec			*exec;
	t_hdoc			*heredoc;
	int				standard[2];
}					t_mini;

typedef enum t_token_type
{
	REDIR_IN,
	REDIR_OUT,
	DBL_REDIR_IN,
	DBL_REDIR_OUT,
	PIPE,
	WORD,
	IN_FILE,
	OUT_FILE,
}					t_token_type;

// syntax error
int					ft_check_redir_in_out(char *str);
int					ft_quote(char *str);

// en
t_env				*ft_lstnew_env(void *content);
t_env				*ft_lstlast_env(t_env *lst);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
t_env				*get_env(char **env);
char				*find_key_for_env(char *my_env);
char				*find_value_for_env(char *my_env);
int					ft_strlen_stop(char *str, char c);
char				*ft_strcat(char *dest, char *src);

// TOKENISATION
int					pipe_nbr(t_mini data);
int					if_is_redir(int type);
void				ft_count_elements(t_mini *data, t_parse *tab);

t_token				*ft_lstnew_tok(void *values);
t_token				*add_prev(t_token *new);
void				ft_lstadd_back_tok(t_token **lst, t_token *new);
void				split_line(int i, char *line, t_token **tokenis);

int					ft_strcmp(const char *s1, const char *s2);
char				*token_negation(char *str);
char				*delete_quote(char *str);
char				*ft_get_key(char *str, int *i);
char				*ft_value_from_key(char *str, t_mini *data);
char				*delete_quote(char *str);
char				*token_positive(char *str);

// FREE
void				free_inside(t_mini *data, char *line, t_parse *tab);
void				free_env(t_mini *data);
void				free_token(t_mini *data);
void				free_parser(t_mini *data, t_parse *tab);
void				free_tab(char **tab);

// MY_PRINTS
void				print_env(t_env *env);
void				print_token(t_token *tokenis);
void				print_parse(t_parse *tab, int size);

// EXPAND
void				ft_expand_len_dollar(t_expand *exp_l);
void				ft_expand_len_dquote(t_expand *exp_l);
void				ft_expand_len_squote(t_expand *exp_l);

int					ft_expand_len(char *str, t_mini *data);
char				*ft_expand(char *str, t_mini *data);

void				ft_cat_value(t_expand *exp, char *value);
void				ft_exp_plus_plus(t_expand *exp_l);

// BUILT_IN
int					ft_is_builtin(t_parse *tab, int i);
int					ft_built_in_comp(t_mini *data, t_parse *tab, int i);
int					ft_env(t_env *env);
int					ft_exit(t_mini *data, t_parse *tab);
int					ft_export(t_mini *data, t_parse *tab);
int					ft_unset(t_mini *data, t_parse *tab);
int					ft_echo(t_parse *tab);
void				print_parse(t_parse *tab, int size);

int					if_is_redir(int type);

// ORGANIS
int					pipe_nbr(t_mini data);
void				ft_parse(t_parse *tab, t_token *tokenis);
int					if_is_redir(int type);
t_parse				*table_struct(t_mini *data);
void				ft_count_elements(t_mini *data, t_parse *tab);

// Free
void				free_env(t_mini *data);

// EXEC
void				free_exec(t_mini *data, char *str);
void				env_in_tab_exec(t_mini *data);
char				**get_path_exec(char **env);
char				*give_way_cmd(char **path, char *cmd);
int					ft_exec(t_mini *data, t_parse *tab);
void				redirections_pipe(t_exec *exec, int index);
int					ft_heredocs(t_mini *data);
#endif