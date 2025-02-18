/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:41:45 by mianni            #+#    #+#             */
/*   Updated: 2024/11/15 14:29:57 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Code operateur : 1 = '<' / 2 = '>' / 3 = '<<' / 4 = '>>' 5 = '&&' / 6 = '||'
// 7 = WILDCARDS / 8 = '|' // 9 = $(...) / 10 = Autre // 11 = '...'
// 12 = "..." // 13 (...)

#include "../minishell.h"

int	execute_command(char *path, t_cmd *cmd, char **env_array)
{
	if (execve(path, cmd->cmd_args, env_array) == -1)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		perror(cmd->cmd_args[0]);
		if (errno == ENOENT)
			exit_now(127);
		if (errno == EACCES)
			exit_now(126);
		exit_now(1);
		return (1);
	}
	return (0);
}

int	prepare_and_execute(t_ast *ast, t_data *data, char **env_array)
{
	char	*path;

	ast->commande->cmd_args = find_wildcards(ast->commande);
	if (open_n_do_builtins(ast->commande, data, ast->commande->files, 0))
		return (1);
	if (ast->commande->type == 11 || ast->commande->type == 12)
		path = get_path_bis(ast->commande->cmd_args[0], env_array);
	else
		path = get_path(ast->commande->cmd_args[0], env_array);
	if (!path)
		return (print_command_not_found(ast->commande->cmd_args[0]));
	if (open_files(ast->commande) == 0)
		return (execute_command(path, ast->commande, env_array));
	else
		exit_now(1);
	return (1);
}

int	command_function(t_ast *ast, t_data *data)
{
	t_env	*env;
	char	**env_array;

	env = get_env(NULL);
	env_array = envlist_to_char(env);
	data = get_data(NULL);
	return (prepare_and_execute(ast, data, env_array));
}

int	exec(t_ast *ast, t_data *data)
{
	if (!ast->commande->cmd_args[0])
		return (0);
	if (ast->commande->type == 5)
		and_function(ast);
	else if (ast->commande->type == 6)
		or_function(ast, data);
	else if (ast->commande->type == 8)
		pipe_function(ast, data);
	else if (ast->commande->type == 7)
		subshell_function(ast, data);
	else if (ast->commande->type >= 10 && ast->commande->type <= 12
		&& ast->commande->cmd_args[0])
		(command_function(ast, data));
	data = get_data(NULL);
	return (0);
}

void	execute(t_ast *top, t_data *data)
{
	if (check_if_fork_needed(top) == true)
		fork_and_exec(top, data);
	else
		exec(top, data);
}
