/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:52:53 by mianni            #+#    #+#             */
/*   Updated: 2024/11/15 14:01:34 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_all_path(char *path, char **env)
{
	int		i;
	char	**cmp;

	i = 0;
	while (env[i] != NULL)
	{
		cmp = ft_split(env[i], '=');
		if (ft_strncmp(path, cmp[0], 5) == 0)
			return (&env[i][5]);
		i++;
	}
	return (0);
}

int	check_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4) != NULL)
			return (1);
		i++;
	}
	return (0);
}

char	*get_path(char *cmd, char **env)
{
	char	**all_path;
	char	**cmd_name;
	char	*temp_path;
	char	*path;
	int		i;

	i = 0;
	if (check_path(env) == 0)
		return (cmd);
	all_path = ft_split(get_all_path("PATH", env), ':');
	cmd_name = ft_split(cmd, ' ');
	if (!cmd_name[0])
		return (cmd);
	if (ft_strchr(cmd_name[0], '/') != NULL)
		return (cmd_name[0]);
	while (all_path[i])
	{
		temp_path = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(temp_path, cmd_name[0]);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

char	*get_path_bis(char *cmd, char **env)
{
	char	**all_path;
	char	*temp_path;
	char	*path;
	int		i;

	i = 0;
	if (check_path(env) == 0)
		return (cmd);
	all_path = ft_split(get_all_path("PATH", env), ':');
	if (cmd)
		return (cmd);
	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	while (all_path[i])
	{
		temp_path = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(temp_path, cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}
