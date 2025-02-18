/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:13:04 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 17:32:38 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	to_many_args(void)
{
	ft_putstr_fd("Minishell: exit: too many arguments\n", STDERR_FILENO);
	return ;
}

int	check_num(char *arg)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (arg[i])
	{
		if (i == 0 && arg[i] == '-')
			return (256 - ft_atoi(&arg[1]));
		if (i == 0 && arg[i] == '+')
			return (ft_atoi(&arg[1]));
		if (ft_isdigit(arg[i]) == 0)
		{
			ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (2);
		}
		i++;
	}
	return (ft_atoi(arg));
}

void	ft_exit(char **args, t_data *data)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	if (!args[1])
		exit_now(data->status);
	if (args[1] && args[2] == NULL)
		exit_now(check_num(args[1]));
	if (args[2])
	{
		status = check_num(args[1]);
		if (status == 2)
			exit_now(status);
		else
			return (data->status = 1, to_many_args());
	}
	if (args[3])
		return (data->status = 1, to_many_args());
}
