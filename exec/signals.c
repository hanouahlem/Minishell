#include "minishell.h"

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

void	sig_management2(int signo)
{
	if (signo == SIGINT)
	{
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
