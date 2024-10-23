/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:44:02 by ahbey             #+#    #+#             */
/*   Updated: 2024/10/23 18:00:58 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote(char *str, int *i, char c)
{
	int	flag;

	flag = 1;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
		{
			flag = 0;
			break ;
		}
		(*i)++;
	}
	return (flag);
}

int	ft_quote(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE || str[i] == SQUOTE)
		{
			flag = ft_check_quote(str, &i, str[i]);
			if (flag == 1)
				break ;
		}
		i++;
	}
	if (flag == 1)
		return (printf("error : syntax\n"), 1);
	return (0);
}

int	ft_check_redir_pipe_begin(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str[i] == W_SPACE || str[i] == W_TAB)
		i++;
	if (str[i] == '|')
	{
		return (1);
	}
	while (str[len] == W_SPACE || str[len] == W_TAB)
		len--;
	if (str[len] == '>' || str[len] == '|' || str[len] == '<')
	{
		return (1);
	}
	return (0);
}

int	ft_check_redir_in_out(char *str)
{
	int	i;

	i = 0;
	if (ft_check_redir_pipe_begin(str) == 1)
		return (printf("Error : syntax"), 1);
	while (str[i])
	{
		if (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<'
			|| str[ft_strlen(str) - 1] == '|' || str[0] == '|')
			return (printf("Error : syntax"), 1);
		if (str[i] == str[i + 1] && str[i] == '|')
			return (printf("Error : syntax"), 1);
		if (str[i] == '<' && str[i + 2] == '<' && str[i + 1] == '>')
			return (printf("Error : syntax"), 1);
		if (str[i] == '>' && str[i + 2] == '>' && str[i + 1] == '<')
			return (printf("Error : syntax"), 1);
		i++;
	}
	return (0);
}

int	syntax_redir(t_token *token)
{
	while (token)
	{
		if (if_is_redir(token->type) == 0)
		{
			token = token->next;
			if (token->type != WORD)
				return (printf("Error : syntax\n"), 1);
		}
		if (token->type == PIPE && token->next->type == PIPE)
			return (printf("Error : syntax\n"), 1);
		token = token->next;
	}
	return (0);
}
