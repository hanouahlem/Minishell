/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:57:40 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/19 19:35:16 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	char	*infile;
	char	*outfile;
	char **cmds;   // Tableau des commandes (cmd1, cmd2, cmd3, ...)
	int **pipes;   // Tableau de pipes (une paire pour chaque commande)
	pid_t *pid;    // Tableau des PID pour chaque fork
	int cmd_count; // Nombre de commandes (argc - 3 ou plus avec heredoc)
	char	**env;
}			t_pipe;

void		free_resources(t_pipe *pex);
int			forking(t_pipe *pex, int i);
void		close_all_pipes(t_pipe *pex);
void		child_infile(t_pipe *pex, int i);
void		child_outfile(t_pipe *pex, int i);
void		child_intermediate(t_pipe *pex, int i);

char		**get_path(char **env);
char		*give_way_cmd(char **path, char *cmd);

void		exec_ve(char *cmd, char **env);
void free_tab(char **str);

#endif