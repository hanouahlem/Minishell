/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:26:49 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/04 15:55:31 by ahbey            ###   ########.fr       */
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

int	syntax(char *line)
{
	// check_guim
	// 	return (1)
	// check syntax
	// return (2)
	(void)line;
	return (0);
}
int	main(int ac, char **av, char **env)
{
	t_mini	data;
	char	*line;
	t_token	*tokenis;

	(void)ac;
	(void)av;
	// signal(SIGINT, sig_management);
	// signal(SIGQUIT, sig_management);
	tokenis = NULL;
	data.token = tokenis;
	data.env = get_env(env);
	while (1)
	{
		line = readline("Minishell $> ");
		if (!line)
			break ;
		if (!*line)
			continue ;
		add_history(line);
		syntax(line);
		if (ft_quote(line))
			continue ;
		if (ft_check_redir_in_out(line) == 1)
			printf("\nERROR ! \n");
		split_line(0, line, tokenis);
		ft_get_key(line, &data);
	}
	// free tout
	return (0);
}

/*

1 - check les guillemets
"'''''''''" vrai        fait
"'" vrai
"""" vrai
'"""""""""""""""' vrai
''' faux
""" faux                       fait
""""""" FAUX

1 - expend
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