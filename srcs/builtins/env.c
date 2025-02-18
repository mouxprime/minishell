/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:13:16 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 15:26:24 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data *data)
{
	t_env	*env;
	int		i;

	i = 0;
	env = get_env(NULL);
	while (env)
	{
		if (env->name && env->name[0] == '?')
			env = env->next;
		if (env)
		{
			if (env->name && env->name[0] != '?')
				printf("%s=", env->name);
			if (env->content && env->name[0] != '?')
				printf("%s\n", env->content);
			env = env->next;
		}
		else
			break ;
	}
	data->status = 0;
}

void	ft_env_export(t_data *data)
{
	t_env	*env;
	int		i;

	(void)data;
	i = 0;
	env = get_env(NULL);
	while (env)
	{
		if (!env->name || (env->name[0] == '?' || env->name[0] == '\0'))
			env = env->next;
		else if (env)
		{
			if (env->name)
				printf("export %s=", env->name);
			if (env->content)
				printf("%c%s%c\n", '"', env->content, '"');
			env = env->next;
		}
		else
			break ;
	}
	data->status = 0;
}
