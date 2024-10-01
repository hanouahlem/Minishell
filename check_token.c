/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:13:20 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/01 16:09:57 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_token(t_mini *data)
{
        while (data->token)
        {
                if (data->token->type == WORD)
                {       
                        data;
                }
        }
}



// < file1 cmd1 option1 | cmd2 option2 > file2

// if (type de redir_in->next == file)
//         next;
//         if (next == cmd)
//                 next;
//                 if (next == opt || PIPE)
//                         next;
//                         if (next == cmd)
//                                 next;
//                                 if (next == opt || PIPE || redir_out)