/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:22:20 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 18:17:26 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*char_to_list(char **envp, t_env *env)
{
	int		i;
	int		j;
	char	*str_name;
	char	*str_content;
	int		len;

	i = 0;
	while (envp[i])
	{
		j = 0;
		len = ft_strlen(envp[i]);
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
				break ;
			j++;
		}
		str_name = ft_substr(envp[i], 0, j, 1);
		str_content = ft_substr(envp[i], j + 1, len + 1, 1);
		env = new_node(env, str_name, str_content);
		i++;
	}
	env = new_node(env, "?", "0");
	return (env);
}

t_env	*new_node(t_env *env, char *name, char *content)
{
	t_env	*new_node;
	t_env	*env_ptr;

	env_ptr = env;
	new_node = ft_malloc(1, (sizeof(t_env)), 1, 0);
	new_node->content = content;
	new_node->name = name;
	new_node->next = NULL;
	if (!env_ptr)
	{
		new_node->prev = NULL;
		env = new_node;
	}
	else
	{
		while (env_ptr->next)
			env_ptr = env_ptr->next;
		env_ptr->next = new_node;
		new_node->prev = env_ptr;
	}
	return (env);
}

t_env	*get_env(t_env *env)
{
	static t_env	*environnement = NULL;

	if (environnement == NULL)
		environnement = env;
	return (environnement);
}

int	count_env_name(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		if (env->name)
			len++;
		env = env->next;
	}
	return (len);
}

char	**envlist_to_char(t_env *env)
{
	int		len;
	t_env	*env_ptr;
	char	**env_array;
	int		i;

	env_ptr = get_env(env);
	len = count_env_name(env);
	i = 0;
	env_array = ft_malloc(len + 1, sizeof(char *), 1, 0);
	env_array[len] = NULL;
	while (env_ptr)
	{
		while ((!env_ptr->name || !env_ptr->content) && env_ptr->next)
			env_ptr = env_ptr->next;
		if (!env_ptr->name || !env_ptr->content)
			break ;
		len = ft_strlen(env_ptr->name) + ft_strlen(env_ptr->content) + 2;
		env_array[i] = ft_malloc(len, sizeof(char), 1, 0);
		copy_str(env_array[i], env_ptr, len);
		i++;
		env_ptr = env_ptr->next;
	}
	return (env_array);
}
