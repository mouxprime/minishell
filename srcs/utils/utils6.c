/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:33:58 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 16:02:50 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files_exit(t_cmd *cmd)
{
	int	dup_status;

	dup_status = 0;
	while (cmd->files)
	{
		if (cmd->files->type == 1)
			cmd->files->fd = ft_open(cmd->files->files_name, O_RDONLY, -2);
		else if (cmd->files->type == 2)
			cmd->files->fd = ft_open(cmd->files->files_name,
					O_TRUNC | O_WRONLY | O_CREAT, -2);
		else if (cmd->files->type == 4)
			cmd->files->fd = ft_open(cmd->files->files_name,
					O_WRONLY | O_APPEND | O_CREAT, -2);
		if (cmd->files->fd == -1)
			return (perror_r("Minishell: ", cmd->files->files_name));
		cmd->files = cmd->files->next;
	}
	return (close_fds(), 0);
}

bool	check_exit(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd_args[0], "exit") == 0)
	{
		if (open_files_exit(cmd) == 0)
			return (printf("exit\n"), ft_exit(cmd->cmd_args, data), true);
		else
			return (exit_status(1, data), true);
	}
	else
		return (false);
}

bool	open_n_do_builtins(t_cmd *cmd, t_data *data, t_files *files,
		int dup_status)
{
	bool	status;
	int		stdin;
	int		stdout;

	if (search_builtins(cmd->cmd_args) == false)
		return (check_exit(cmd, data));
	if (!files)
		return (do_builtins(cmd->cmd_args, data));
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (open_files(cmd) == -1)
		return (close(stdin), close(stdout), data->status = 1, true);
	else
	{
		status = do_builtins(cmd->cmd_args, data);
		if (files->type == 1 || files->type == 3)
			dup_status = dup2(stdin, STDIN_FILENO);
		else if (files->type == 2 || files->type == 4)
			dup_status = dup2(stdout, STDOUT_FILENO);
		if (dup_status == -1)
			return (close(stdin), close(stdout), perror_r("Minishell: dup2: ",
					files->files_name), false);
		return (close(stdin), close(stdout), status);
	}
}

void	print_double_array(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			ft_putchar(str[i][j]);
			j++;
		}
		write(1, "$", 1);
		write(1, "\n", 1);
		i++;
	}
}

bool	check_signal(t_data *data, char *str_bis)
{
	if (g_status != 0 || data->signaled != 0)
	{
		get_data(NULL)->status = g_status;
		g_status = 0;
		data->signaled = 0;
		return (free(str_bis), false);
	}
	return (true);
}
