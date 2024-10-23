/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:26:49 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/21 18:17:38 by manbengh         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_mini	data;
	char	*line;

	(void)ac;
	(void)av;
	// signal(SIGINT, sig_management);
	// signal(SIGQUIT, sig_management);
	// tokenis = NULL;
	data.env = get_env(env);
	data.token = NULL;
	while (1)
	{
		line = readline("Minishell $> ");
		if (!line)
			break ;
		if (!*line)
			continue ;
		add_history(line);
		if (ft_quote(line))
			continue ;
		if (ft_check_redir_in_out(line) == 1)
			printf("\nERROR ! \n");
		split_line(0, line, &data.token);
		printf("AVANT:[%s]\n", line);
		// line = ft_expand(line, &data);
		// printf("APRES:[%s]\n", data->); // cause un read of size
		// printf("%svalue+t ----> %s%s\n", RED, data.token->value_t, RESET);
		// if (ft_built_in_comp(&data) == 1)
		// 	printf("ERROR ENV !\n");
		ft_cmd_organis(&data);
		printf("APRES:[%s]\n\n", line);
		free_inside(&data, line);
	}
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