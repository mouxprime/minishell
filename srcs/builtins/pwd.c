/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:13:23 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 15:28:19 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_data *data)
{
	char	*command1;
	char	*cwd;

	command1 = ft_malloc(4096, sizeof(char), 0, 0);
	cwd = getcwd(command1, 4096);
	printf("%s\n", cwd);
	data->status = 0;
}
