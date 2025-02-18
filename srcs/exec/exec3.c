/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:26:31 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 15:21:56 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_and_exec(t_ast *ast, t_data *data)
{
	int	pid1;
	int	status;

	status = 0;
	pid1 = fork();
	if (pid1 == 0)
	{
		set_child_signals();
		data->is_child = 1;
		exec(ast, data);
	}
	waitpid(pid1, &status, 0);
	exit_status(status, data);
	return ;
}

bool	check_if_fork_needed(t_ast *ast)
{
	if (!ast->commande->cmd_args[0])
		return (false);
	if (ft_strcmp(ast->commande->cmd_args[0], "exit") == 0)
		return (false);
	if (ast->commande->type == 7 || (ast->commande->type >= 10
			&& ast->commande->type <= 12
			&& search_builtins(ast->commande->cmd_args) == false))
		return (true);
	return (false);
}

void	and_function(t_ast *ast)
{
	t_data	*data;

	data = get_data(NULL);
	if (check_if_fork_needed(ast->left) == true)
		fork_and_exec(ast->left, data);
	else
		exec(ast->left, data);
	if (data->status == 0)
	{
		if (check_if_fork_needed(ast->right) == true)
			fork_and_exec(ast->right, data);
		else
			exec(ast->right, data);
	}
}

void	or_function(t_ast *ast, t_data *data)
{
	if (check_if_fork_needed(ast->left) == true)
		fork_and_exec(ast->left, data);
	else
		exec(ast->left, data);
	if (data->status != 0)
	{
		if (check_if_fork_needed(ast->right) == true)
			fork_and_exec(ast->right, data);
		else
			exec(ast->right, data);
	}
	else
		return ;
}

int	subshell_function(t_ast *ast, t_data *data)
{
	t_ast	*ast_list;
	t_env	*env_list;

	env_list = get_env(NULL);
	ast_list = parsing(ft_substr(ast->commande->cmd_args[0], 1,
				ft_strlen(ast->commande->cmd_args[0]) - 2, 0), env_list);
	if (!ast_list->commande->cmd_args[0])
		return (0);
	execute(ast_list, data);
	exit_now(data->status);
	return (0);
}
