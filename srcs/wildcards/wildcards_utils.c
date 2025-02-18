/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:02:15 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/12 14:20:18 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dir_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		i++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (i);
}

int	count_len_malloc(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		i++;
	return (i);
}

char	*remove_star(char *files)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (files[i] == '*')
		{
			files = ft_strjoin(ft_substr(files, 0, i, 0), &files[i + 1]);
			i = 0;
			continue ;
		}
		i++;
	}
	return (files);
}

char	**create_files_tab(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i;

	i = count_dir_files();
	dir = opendir(".");
	files = ft_malloc(i + 1, sizeof(char *), 0, 0);
	i = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		files[i] = ft_strdup(entry->d_name);
		i++;
		entry = readdir(dir);
	}
	files[i] = NULL;
	closedir(dir);
	return (files);
}
