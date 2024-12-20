#include "minishell.h"

// void    sign_hdoc(int num_sig)
// {
// 	int		i;

// 	i = -1;
// 	(void)num_sig;
// 	static t_mini	data = {0,
// 		.standard[0] = -1,
// 		.standard[1] = -1
// 	};
// 	write(1, "\n", 1);
// 	while (++i < data.nbr_hd)
// 	{
// 		close(data.heredoc[i].pipe_fd[1]);
// 		close(data.heredoc[i].pipe_fd[0]);
// 	}
// 	// if (data.flag_hd == 1)
// 	// {
// 	// 	dup2(data.std_fd[0], STDIN_FILENO);
// 	// 	dup2(data.std_fd[1], STDOUT_FILENO);
// 	// 	close(data.std_fd[0]);
// 	// 	close(data.std_fd[1]);
// 	// 	free_tab(data.builtin);
// 	// }
// 	// free_export(data.env_export);
// 	// free_tok(&data.tok);
// 	// free(data.heredoc);
// 	// exit(130);
//     free_exec(&data, NULL, 130);
// }

void	sig_management(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		if (!sign_return)
			sign_return = 130;
		else
			sign_return = 0;
	}
}

void	manage_sig(void)
{
    struct sigaction sa;

    // Initialiser la structure sigaction à zéro
    sigemptyset(&sa.sa_mask);  // Aucun signal ne sera bloqué pendant l'exécution du gestionnaire
    sa.sa_handler = sig_management;  // Définir le gestionnaire pour SIGINT
    sa.sa_flags = 0;  // Pas d'options supplémentaires

    // Enregistrer le gestionnaire pour SIGINT
    sigaction(SIGINT, &sa, NULL);
	// signal(SIGINT, &sig_management);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGTSTP, SIG_IGN);
}

// void	disable_signals(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	default_signals(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }