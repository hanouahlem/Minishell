/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organis_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:57:11 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/23 15:11:31 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg_to_cmd(t_parse *cmd, char *arg)
{
	char	**new_args;
	int		i;

	// Compter le nombre d'arguments existants
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	// Copier les anciens arguments dans le nouveau tableau
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		// printf("new_args == %s\n", new_args[i]);
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	// Libérer l'ancien tableau d'arguments
	if (cmd->args)
		free(cmd->args);
	// Mettre à jour cmd->args avec le nouveau tableau
	cmd->args = new_args;
}

t_parse	*create_cmd(t_parse *new_cmd, t_mini *data)
{
	new_cmd = malloc(sizeof(t_parse));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	// new_cmd->num_redir_in = 0;
	// new_cmd->num_redir_out = 0;
	new_cmd->tok = data->token;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

// void	ft_cmd_organis(t_mini *data)
// {
// 	t_parse	*cmd;
// 	int		skip_arg;

// 	skip_arg = 0;
// 	cmd = NULL;
// 	// print_token(data->token);
// 	while (data->token)
// 	{
// 		if (data->token->type != PIPE)
// 		{
// 			// gerer echo hello > f1 > f2 > f3 > f4 on doit ecrire que dans f4
// 			if (data->token->type == WORD)
// 			{
// 				if (!skip_arg)
// 				{
// 					if (!cmd || (data->token->prev
// 							&& data->token->prev->type == PIPE))
// 					{
// 						cmd = create_cmd(cmd, data);
// 						cmd->cmd = ft_strdup(data->token->value_t);
// 						printf("cmd = %s\n", cmd->cmd);
// 					}
// 					else
// 					{
// 						add_arg_to_cmd(cmd, data->token->value_t);
// 						printf("arg = %s\n", data->token->value_t);
// 					}
// 				}
// 				else
// 					skip_arg = 0;
// 			}
// 			// Gérer les redirections
// 			else if (data->token->type == REDIR_IN)
// 			{
// 				if (data->token->next && data->token->next->type == WORD)
// 				{
// 					data->token->type = IN_FILE;
// 					// printf("data->token->type ====> [%d]\n",
// 					// data->token->type);
// 					// printf("data->token->val ====> [%s]\n",
// 					// data->token->value_t);
// 					skip_arg = 1;
// 				}
// 			}
// 			else if (data->token->type == REDIR_OUT)
// 			{
// 				if (data->token->next && data->token->next->type == WORD)
// 				{
// 					data->token->type = OUT_FILE;
// 					// printf("data->token->type ====> [%d]\n",
// 					// data->token->type);
// 					// printf("data->token->val ====> [%s]\n",
// 					// data->token->value_t);
// 					skip_arg = 1;
// 				}
// 			}
// 		}
// 		else if (data->token->type == PIPE)
// 		{
// 			printf("il y a un PIPE, on passe a la commande suivante\n");
// 			cmd = NULL; // Réinitialiser pour la prochaine commande
// 		}
// 		data->token = data->token->next;
// 	}
// }

void	ft_organis_redir(t_mini *data, int *skip_arg)
{
	if ((data->token->type == REDIR_IN || data->token->type == REDIR_OUT)
		&& data->token->next && data->token->next->type == WORD)
	{
		if (data->token->type == REDIR_IN)
		{
			data->token->next->type = IN_FILE;
			printf("type == %d\n", data->token->next->type);
			printf("value == %s\n", data->token->next->value_t);
		}
		else if (data->token->type == REDIR_OUT)
		{
			data->token->next->type = OUT_FILE;
			printf("type == %d\n", data->token->next->type);
			printf("value == %s\n", data->token->next->value_t);
		}
		*skip_arg = 1;
	}
}

void	ft_organis_cmd_arg(t_mini *data, t_parse **cmd, int *skip_arg)
{
	if (data->token->type == WORD && !(*skip_arg))
	{
		if (!(*cmd) || (data->token->prev && data->token->prev->type == PIPE))
		{
			*cmd = create_cmd(*cmd, data);
			(*cmd)->cmd = ft_strdup(data->token->value_t);
			printf("cmd = %s\n", (*cmd)->cmd);
		}
		else
		{
			add_arg_to_cmd(*cmd, data->token->value_t);
			printf("arg = %s\n", data->token->value_t);
		}
	}
	else
		*skip_arg = 0;
}

void	ft_cmd_organis(t_mini *data)
{
	t_parse	*cmd;
	int		skip_arg;

	cmd = NULL;
	skip_arg = 0;
	while (data->token)
	{
		if (data->token->type != PIPE)
		{
			ft_organis_cmd_arg(data, &cmd, &skip_arg);
			ft_organis_redir(data, &skip_arg);
		}
		else
		{	printf("cmd===> {%s}\n", cmd->cmd);
			printf("arg[0]===> {%s}\n", cmd->args[0]);
			printf("arg[1]===> {%s}\n", cmd->args[1]);
			printf("arg[2]===> {%s}\n", cmd->args[2]);
			cmd = NULL;
			printf("il y a un PIPE, on passe a la commande suivante\n");
		}
		data->token = data->token->next;
		
	}
}
