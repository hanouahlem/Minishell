/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organis_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:57:11 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/16 16:09:55 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_cmd_organis(t_mini *data)
// {	
// 	print_token(data->token);
// 	while (data->token  && data->token->type != PIPE)
// 	{
// 		if(data->token->type == WORD)
// 		{
// 			if (data->token->prev == NULL)
// 				printf("token : %s  CMDDD\n", data->token->value_t);
// 			else if (data->token->prev && data->token->prev->type == REDIR_IN)
// 			{
// 				data->token->type = IN_FILE;
// 				printf("data->token->type ====> [%d]\n", data->token->type);
// 				printf("data->token->val ====> [%s]\n", data->token->value_t);
// 				// data->token = data->token->next;
// 			}
// 			else if (data->token->prev && data->token->prev->type == REDIR_OUT)
// 			{
// 				data->token->type = OUT_FILE;
// 				printf("data->token->type ====> [%d]\n", data->token->type);
// 				printf("data->token->val ====> [%s]\n", data->token->value_t);
// 				// data->token = data->token->next;
// 			}
// 			else
// 			{
// 				printf("ouuuuuuiiii\n");
// 			}
// 		}
// 		data->token = data->token->next;
// 	}
// }

void	ft_cmd_organis(t_mini *data)
{	
	print_token(data->token);
	data->cmd = NULL;
	while (data->token)
	{
		if (data->token->type != PIPE)
		{
			if(data->token->type == WORD)
			{
				if (data->token->prev == NULL)
				{
					data->cmd[0] = ft_strjoin(data->cmd[0], data->token->value_t);
					printf("cmd : %s\n", data->cmd[0]);
					printf("token : %s  CMDDD\n", data->token->value_t);
				}
				else if (data->token->prev && data->token->prev->type == REDIR_IN)
				{
					data->token->type = IN_FILE;
					printf("data->token->type ====> [%d]\n", data->token->type);
					printf("data->token->val ====> [%s]\n", data->token->value_t);
					// data->token = data->token->next;
				}
				else if (data->token->prev && data->token->prev->type == REDIR_OUT)
				{
					data->token->type = OUT_FILE;
					printf("data->token->type ====> [%d]\n", data->token->type);
					printf("data->token->val ====> [%s]\n", data->token->value_t);
					// data->token = data->token->next;
				}
			}
		}
		data->token = data->token->next;
	}
}
