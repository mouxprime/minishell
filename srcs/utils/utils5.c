/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:33:58 by mianni            #+#    #+#             */
/*   Updated: 2024/11/15 14:29:56 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_status(int status, t_data *data)
{
	t_env	*env;

	env = get_env(NULL);
	if (WIFSIGNALED(status))
	{
		data->status = 128 + WTERMSIG(status);
		data->signaled = 1;
	}
	else if (WIFSTOPPED(status))
		data->status = 128 + WSTOPSIG(status);
	else if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	search_in_env(env, data);
}

int	count_len(char *command_line)
{
	int	i;
	int	len;

	i = 0;
	len = 1;
	while (command_line[i])
	{
		while (ft_isalnum(command_line[i] != 1 || command_line[i] != ' '
				|| command_line[i] != '\t'))
		{
			len++;
			i++;
		}
		i++;
	}
	return (len);
}

void	initialize_data(t_data *data, t_env **env_list, char **envp)
{
	*env_list = char_to_list(envp, *env_list);
	get_env(*env_list);
	ft_bzero(data, sizeof(t_data));
	get_data(data);
	print_animation();
}

bool	option_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && i == 0)
			i++;
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	print_command_not_found(char *cmd)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Command not found\n", STDERR_FILENO);
	exit_now(127);
	return (1);
}
