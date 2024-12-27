/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:23:25 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/26 21:10:32 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	sig_management(int signo)
{
	sign_return = 128 + signo;
	rl_done = 1;
}

// void	sig_management2(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		if (!sign_return)
// 			sign_return = 130;
// 		else
// 			sign_return = 0;
// 	}
// }

void	manage_sig(void)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
	rl_event_hook = sig_event;
    sa.sa_handler = sig_management; 
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}