/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:26:49 by ahbey             #+#    #+#             */
/*   Updated: 2024/09/18 18:51:01 by manbengh         ###   ########.fr       */
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

int syntax(char *line)
{
	// check_guim
	// 	return (1)
	// check syntax 
	// return (2)
	(void)line;
	printf("hello\n");
	return (0);
}
int main()
{
    char *line;
	
	// signal(SIGINT, sig_management);
	// signal(SIGQUIT, sig_management);
    while (1)
	{
		line = readline("Minishell ");
		if (!line)
			break ;
		if (!*line)
			continue ;
		syntax(line);
		ft_quote(line);
		add_history(line);
		if (ft_fleche(line) == 1)
			printf("No fleeeeches !\n");
    }
    return (0);
}

/*

1 - check les guillemets
"'''''''''" vrai 
"'" vrai
"""" vrai
'"""""""""""""""' vrai
''' faux
""" faux
""""""" FAUX

1 - expend
$USER == ahlem  -> "$USER"== "ahlem" ->  '$USER' == '$USER' 

2- METTRE EN NEGATIVE L'INTERRIEUR DES GUILLEMETS
"bonjour ||||| c moi"
"*******************"

3 - gerer la syntax 

|| faux 
>>> faux
|       | faux
command | faux
| command |
>  > faux
"|||||" vrai
'<><><||||<><' vrai

4 - remettre en positive
"****************"
"bonjour || c moi"

5 - tokenisation

*/