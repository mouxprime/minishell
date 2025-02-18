/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:13:09 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 15:19:47 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **path, int i, t_data *data)
{
	if (!path[1])
	{
		ft_putstr_fd("Minishell: cd: No such file or directory\n",
			STDERR_FILENO);
		return (data->status = 1, 1);
	}
	if (chdir(path[i + 1]) == -1)
	{
		perror("cd");
		return (data->status = 1, 1);
	}
	return (data->status = 0, 0);
}
