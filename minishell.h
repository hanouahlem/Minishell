/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:39:23 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/16 16:04:06 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Colors.h"
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
	char			*str_len;
	int				i;
	int				i_len;
	char			*new_str;
	char			*new_str_len;
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

typedef struct t_mini
{
	char			*data;
	char			msg_error;
	char			**cmd;
	char			**cmd_opt;
	t_token			*token;
	t_env			*env;
	t_expand		*expand;
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

int					ft_check_redir_in_out(char *str);
int					ft_quote(char *str);

t_env				*ft_lstnew_env(void *content);
t_env				*ft_lstlast_env(t_env *lst);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
char				*ft_strcat(char *dest, char *src);

t_token				*ft_lstnew_tok(void *values);
t_token				*add_prev(t_token *new);
void				ft_lstadd_back_tok(t_token **lst, t_token *new);
void				split_line(int i, char *line, t_token **tokenis);

t_env				*get_env(char **env);
char				*find_key_for_env(char *my_env);
char				*find_value_for_env(char *my_env);
int					ft_strlen_stop(char *str, char c);
void				ft_cmd_organis(t_mini *data);

int					ft_strcmp(const char *s1, const char *s2);
char				*token_negation(char *str);

char				*delete_quote(char *str);

char				*ft_get_key(char *str, int *i);
char				*ft_value_from_key(char *str, t_mini *data);
char				*retirerquote(char *str);
void				token_positive(char *str);
// void	free_everything(t_mini *data, t_token *tokenis);


void	free_inside(t_mini *data, char *line);
void	print_token(t_token *tokenis);


// Expand
void				ft_expand_len_dollar(t_expand *exp_l);
void				ft_expand_len_dquote(t_expand *exp_l);
void				ft_expand_len_squote(t_expand *exp_l);

int					ft_expand_len(char *str, t_mini *data);
char				*ft_expand(char *str, t_mini *data);

void				ft_cat_value(t_expand *exp, char *value);
void				ft_exp_plus_plus(t_expand *exp_l);

// BUILT_IN

int					ft_env(t_mini *data);
int					ft_built_in_comp(t_mini *data);
int					ft_exit(t_mini *data);
int					ft_export(t_mini *data);
int					ft_unset(t_mini *data);

#endif