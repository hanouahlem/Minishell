/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:26:49 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/02 20:47:24 by ahbey            ###   ########.fr       */
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
	char	*test;
	char	*test2;

	(void)ac;
	(void)av;
	// (void)env;
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
		test2 = token_negation(line);
		printf("test apres negation = %s\n", test2);
		if (ft_check_redir_in_out(line) == 1)
			printf("\nERROR ! \n");
		test2 = token_negation(test2);
		printf("test apres posi = %s\n", test2);
		test = delete_quote(line);
		printf("%s\n", test);
		split_line(line, tokenis);
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