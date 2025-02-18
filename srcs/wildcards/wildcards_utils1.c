/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:16:24 by mianni            #+#    #+#             */
/*   Updated: 2024/11/12 14:20:29 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_files(char **files, char *cmd_it, char **new_cmd, int *i)
{
	int	j;
	int	is_find;

	j = 0;
	is_find = 0;
	while (files[j])
	{
		if (found_files(files[j], cmd_it) == 0)
		{
			new_cmd[*i] = files[j];
			(*i)++;
			is_find++;
		}
		j++;
	}
	return (is_find);
}

char	**create_cmd_tab(char **cmd, int len_malloc, char **files, int it)
{
	char	**new_cmd;
	int		i;
	int		c;

	i = 0;
	c = 0;
	new_cmd = ft_malloc(len_malloc + 1, sizeof(char *), 0, 0);
	while (i < len_malloc)
	{
		if (i == it)
		{
			if (!fill_files(files, cmd[it], new_cmd, &i))
				new_cmd[i++] = cmd[it];
			c++;
		}
		else
			copy_remaining_cmd(cmd, new_cmd, &i, &c);
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}

char	**expand_wildcard(char **cmd, int it)
{
	char	**files;
	int		len_malloc;
	int		len_malloc2;
	int		i;

	i = 0;
	len_malloc2 = 0;
	len_malloc = count_len_malloc(cmd);
	files = create_files_tab();
	while (files[i])
	{
		if (found_files(files[i], cmd[it]) == 0)
		{
			len_malloc2++;
		}
		i++;
	}
	if (len_malloc2 > 0)
		len_malloc += len_malloc2 - 1;
	return (create_cmd_tab(cmd, len_malloc, files, it));
}

char	**find_wildcards(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[i])
	{
		if (ft_strchr(cmd->cmd_args[i], '*'))
			cmd->cmd_args = expand_wildcard(cmd->cmd_args, i);
		i++;
	}
	return (cmd->cmd_args);
}
