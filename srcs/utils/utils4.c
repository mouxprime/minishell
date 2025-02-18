/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:42:18 by mianni            #+#    #+#             */
/*   Updated: 2024/11/12 16:02:14 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	search_builtins(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], "cd") == 0)
			return (true);
		if (ft_strcmp(command[i], "echo") == 0)
			return (true);
		if (ft_strcmp(command[i], "env") == 0)
			return (true);
		if (ft_strcmp(command[i], "export") == 0)
			return (true);
		if (ft_strcmp(command[i], "pwd") == 0)
			return (true);
		if (ft_strcmp(command[0], "unset") == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	do_builtins(char **command, t_data *data)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (ft_strncmp(command[i], "cd", ft_strlen(command[i])) == 0)
			return (ft_cd(command, i, data), true);
		if (ft_strncmp(command[i], "echo", ft_strlen(command[i])) == 0)
			return (ft_echo(&command[0], data), true);
		if (ft_strncmp(command[i], "env", ft_strlen(command[i])) == 0)
			return (ft_env(data), true);
		if (ft_strncmp(command[i], "export", ft_strlen(command[i])) == 0)
			return (ft_export(&command[i], data), true);
		if ((ft_strncmp(command[i], "pwd", ft_strlen(command[i])) == 0))
			return (ft_pwd(data), true);
		if (ft_strncmp(command[0], "unset", ft_strlen(command[i])) == 0)
			return (ft_unset(command), true);
		i++;
	}
	return (false);
}

char	*copy_str(char *env_array, t_env *env, int len)
{
	int	i;
	int	iter;

	(void)len;
	i = 0;
	iter = 0;
	if (!env->name || !env->content)
		return (NULL);
	while (env->name[iter])
		env_array[i++] = env->name[iter++];
	env_array[i++] = '=';
	iter = 0;
	while (env->content[iter])
		env_array[i++] = env->content[iter++];
	env_array[i] = '\0';
	return (env_array);
}

int	index_return(char c, char *command_line)
{
	int	index;

	index = 0;
	while (command_line[index] != c && command_line[index])
		index++;
	if (command_line[index] == c)
		return (index);
	else
		return (-1);
}

t_data	*get_data(t_data *data_ptr)
{
	static t_data	*data = NULL;

	if (data == NULL)
		data = data_ptr;
	return (data);
}
