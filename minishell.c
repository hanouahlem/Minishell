/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:26:49 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/13 18:50:24 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	sig_management(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

int	is_space_or_tab(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] == ' ') || str[i] == '\t')
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	static	t_mini data = {0};
	char	*line;
	t_parse	*tab = NULL;
	// char *str = NULL;
	(void)ac;
	(void)av;
	// signal(SIGINT, sig_management);
	// signal(SIGQUIT, sig_management);
	
	data.env = get_env(env);
	line = NULL;
	while (1)
	{
		// ft_init(&data);
		data.exit_status = 0;
		line = readline("Minishell 😜👀$> ");
		if (!line)
			break ;
		if (!*line)
			continue ;
		// check si ligne espace ou tab only;
		if (is_space_or_tab(line) == 1)
		{
			free_inside(&data, line, tab);
			continue;
		}
		add_history(line);
		line = token_negation(line);
		if (ft_quote(line))
		{
			free(line);
			continue ;
		}
		if (ft_check_redir_in_out(line) == 1)
		{
			free(line);
			continue ;
		}
		line = token_positive(line);
		line  = ft_expand(line, &data);
		split_line(-1, line, &data.token);
		// printf(	"AVANT:[%s]\n", line);
		tab = table_struct(&data);
		if (ft_built_in_comp(&data, tab, line) == 1)
			;
		// printf("\nAPRES:[%s]\n", line);
		free_inside(&data, line, tab);
	}
	free(line);
	free_env(&data);
	// rl_clear_history();
	return (0);
}
/*
printf("%svalue+t ----> %s%s\n", RED, data.token->value_t, RESET);

1 - check les guillemets
"'''''''''" vrai        fait
"'" vrai
"""" vrai
'"""""""""""""""' vrai
''' faux
""" faux                       fait
""""""" FAUX

1 - expand
$USER == ahlem  -> "$USER"== "ahlem" ->  '$USER' == '$USER'

2- METTRE EN NEGATIVE L'INTERRIEUR DES GUILLEMETS         faiiiiit
"bonjour ||||| c moi"
"*******************"

3 - gerer la syntax

|| faux
>>> faux
|       | faux
command | faux
| command |                 fait
>  > faux
"|||||" vrai
'<><><||||<><' vrai

4 - remettre en positive
"****************"         fait
"bonjour || c moi"

5 - tokenisation

*/