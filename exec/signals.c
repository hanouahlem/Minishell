/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:23:25 by ahbey             #+#    #+#             */
/*   Updated: 2024/12/30 15:43:48 by manbengh         ###   ########.fr       */
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

void	signal_pipex(int signum)
{
	if (signum == SIGQUIT)
		sign_return = SIGQUIT;
	else
		sign_return = SIGINT;
}

void	manage_sig(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	rl_event_hook = sig_event;
	sa.sa_handler = sig_management;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
