/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:26:49 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/24 12:17:41 by ahbey            ###   ########.fr       */
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

void	ft_init(t_mini *data)
{
	data->args = NULL;
	data->cmd = NULL;
	data->token = NULL;
	data->parser = NULL;
}

int	main(int ac, char **av, char **env)
{
	static	t_mini data = {0};
	char	*line;
	t_parse	*tab = NULL;
	(void)ac;
	(void)av;
	// signal(SIGINT, sig_management);
	// signal(SIGQUIT, sig_management);
	// tokenis = NULL;
	data.env = get_env(env);
	while (1)
	{
		ft_init(&data);
		line = readline("Minishell $> ");
		if (!line)
			break ;
		if (!*line)
			continue ;
		add_history(line);
		if (ft_quote(line))
			continue ;
		if (ft_check_redir_in_out(line) == 1)
			continue ;
		split_line(-1, line, &data.token);
		printf("AVANT:[%s]\n", line);
		// if(syntax_redir(data.token) == 1)
		// 	continue ;
		line = ft_expand(line, &data);
		// printf("APRES:[%s]\n", data->); // cause un read of size
		// printf("%svalue+t ----> %s%s\n", RED, data.token->value_t, RESET);
		tab = table_struct(&data);
		if (ft_built_in_comp(&data, tab) == 1)
			printf("ERROR ENV !\n");
		printf("APRES:[%s]\n", line);
		// free_inside(&data, line);
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