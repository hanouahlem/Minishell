/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:39 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/19 18:55:22 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exec_ve(char *cmd, char **env)
{
    char **way = get_path(env);
    char **cmd_split = ft_split(cmd, ' ');
    if (!cmd_split)
    {
        free_tab(way);
        exit(1);
    }
    cmd = give_way_cmd(way, cmd_split[0]);
    if (!cmd)
        return (free_tab(way), free_tab(cmd_split), exit(1));
    execve(cmd, cmd_split, env);
    free(cmd);
    free_tab(cmd_split);
}
