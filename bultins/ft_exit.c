/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:36:48 by ahbey             #+#    #+#             */
/*   Updated: 2024/11/19 15:25:54 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi_flag(const char *str, int *flag)
{
	int	i;
	long	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	if (ft_strlen(str) > 11)
		return (*flag = 1, 0);
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb * sign < -2147483648 || nb * sign > 2147483647)
		return (*flag = 1, 0);
	return (nb * sign);
}

int	ft_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
void	one_arg(t_mini *data, char *args)
{
	int	flag;
	int	val;

	flag = 0;
	val = ft_atoi_flag(args, &flag);
	if (flag == 1)
	{
		printf("minishell: exit: %s: numeric argument required \n", args);
		data->exit_status = 2;
	}
	else
		data->exit_status = val % 256;
}

int	ft_exit(t_mini *data, t_parse *tab, char *line)
{
	printf("exit\n");
	if (tab->args[1] && tab->args[2])
	{
		data->exit_status = 1;
		printf("minishell: exit: %s: too many arguments !\n", tab->args[1]);
		return (1);
	}
	else if (tab->args[1] && ft_digits(tab->args[1]) == 1)
	{
		data->exit_status = 255;
		printf("minishell: exit: %s: numeric argument required \n", tab->args[1]);
	}
	else if (tab->args[1])
		one_arg(data, tab->args[1]);
	else
		data->exit_status = 0;
	free_inside(data, line, tab);
	free_env(data);
	exit(1);
	return (0);
}

