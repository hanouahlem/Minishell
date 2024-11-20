/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:36 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/19 18:56:34 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_path(char **env)
{
    while (*env)
    {
        if (ft_strncmp(*env, "PATH=", 5) == 0)
            return (ft_split(*env + 5, ':'));
        env++;
    }
    return (NULL);
}

char *give_way_cmd(char **path, char *cmd)
{
    char *path_tmp;
    char *res;

    while (*path)
    {
        path_tmp = ft_strjoin(*path, "/");
        res = ft_strjoin(path_tmp, cmd);
        free(path_tmp);
        if (access(res, X_OK) == 0)
            return (res);
        free(res);
        path++;
    }
    return (NULL);
}
