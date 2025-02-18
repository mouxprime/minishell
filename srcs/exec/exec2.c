/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:25:29 by mianni            #+#    #+#             */
/*   Updated: 2024/11/13 15:27:03 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_child_process(int fd[2], t_ast *ast, t_data *data)
{
	if (dup2(fd[1], 1) == -1)
		perror("Minishell : dup2 error ");
	close(fd[0]);
	close(fd[1]);
	exec(ast->left, data);
	exit_now(get_data(NULL)->status);
}

void	second_child_process(int fd[2], t_ast *ast, t_data *data)
{
	if (dup2(fd[0], 0) == -1)
		perror("Minishell : dup2 error ");
	close(fd[1]);
	close(fd[0]);
	exec(ast->right, data);
	exit_now(get_data(NULL)->status);
}

void	wait_for_children(int pid1, int pid2, t_data *data)
{
	int	status;

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	exit_status(status, data);
}

void	pipe_function(t_ast *ast, t_data *data)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (perror("Minishell : pipe error"));
	pid1 = fork();
	if (pid1 == -1)
		return (close(fd[0]), close(fd[1]),
			perror("Minishell : pipe fork(1) error"));
	if (pid1 == 0)
		first_child_process(fd, ast, data);
	pid2 = fork();
	if (pid2 == -1)
		return (close(fd[0]), close(fd[1]),
			perror("Minishell : pipe fork(2) error"));
	if (pid2 == 0)
		second_child_process(fd, ast, data);
	close(fd[0]);
	close(fd[1]);
	wait_for_children(pid1, pid2, data);
}
