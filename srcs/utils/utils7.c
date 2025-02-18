/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:53:53 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/14 19:02:31 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	search_in_env(t_env *env, t_data *data)
{
	while (env)
	{
		if (env->name && env->name[0] == '?' && !env->name[1])
		{
			env->content = ft_itoa(data->status);
			return (true);
		}
		env = env->next;
	}
	return (false);
}

bool	check_parenthesis(char *str)
{
	int	i;
	int	parenthesis;

	i = 0;
	parenthesis = 0;
	while (str[i])
	{
		if (str[i] == '(')
			parenthesis++;
		if (str[i] == ')')
			parenthesis--;
		i++;
	}
	if (parenthesis == 0)
		return (true);
	else
		return (false);
}

bool	check_files_cmd_exist_left(t_ast *ast_list)
{
	int	count;

	count = 0;
	if (!ast_list->commande->cmd_args[0])
	{
		if (ast_list->commande->files)
			open_files(ast_list->commande);
		count++;
	}
	if (ast_list->left)
	{
		return (check_files_cmd_exist_left(ast_list->left));
	}
	if (count > 0)
		return (false);
	return (true);
}

bool	check_files_cmd_exist_right(t_ast *ast_list)
{
	int	count;

	count = 0;
	if (!ast_list->commande->cmd_args[0])
	{
		if (ast_list->commande->files)
			open_files(ast_list->commande);
		count++;
	}
	if (ast_list->right)
	{
		return (check_files_cmd_exist_right(ast_list->right));
	}
	if (count > 0)
		return (false);
	return (true);
}

void	error_export(char *command_line)
{
	ft_putstr_fd("incorrect pattern for export: '", STDERR_FILENO);
	ft_putstr_fd(command_line, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
