/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:13:13 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 15:25:31 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_n(char **command_line)
{
	int	i;
	int	j;

	i = 2;
	while (command_line[i])
	{
		j = 0;
		if (option_n(command_line[i]) == true)
		{
			i++;
			continue ;
		}
		while (command_line[i][j])
		{
			ft_putchar(command_line[i][j]);
			j++;
		}
		if (command_line[i + 1])
			write(1, " ", 1);
		i++;
	}
}

bool	other_quote_inside(char *str, int i, int j)
{
	int	k;
	int	l;

	(void)i;
	k = 0;
	l = 0;
	while (str[k])
	{
		if (is_a_quote(str[k]) == true && k != j)
			l++;
		k++;
	}
	if (l % 2 == 1)
		return (true);
	return (false);
}

int	check_dollar_status(char **command_line, t_data *data)
{
	if (command_line[1][0] == '$' && command_line[1][1] == '?')
	{
		ft_printf("%d\n", data->status);
		return (1);
	}
	return (0);
}

void	print_echo_arguments(char **command_line)
{
	int	i;
	int	j;

	i = 1;
	while (command_line[i])
	{
		j = 0;
		while (command_line[i][j])
		{
			ft_putchar(command_line[i][j]);
			j++;
		}
		if (command_line[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	ft_echo(char **command_line, t_data *data)
{
	if (!command_line[1])
	{
		write(1, "\n", 1);
		data->status = 0;
		return ;
	}
	if (command_line[1][0] == '-' && option_n(&command_line[1][1]))
		echo_n(command_line);
	else if (check_dollar_status(command_line, data) == 0)
	{
		print_echo_arguments(command_line);
		write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	data->status = 0;
}
