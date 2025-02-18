/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:44:13 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/14 15:00:56 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	exit_now(int status)
{
	close_fds();
	ft_malloc(0, 0, 2, status);
}

void	clear_soft_data(void)
{
	ft_malloc(0, 0, 3, 0);
}

void	print_trash_list(void)
{
	ft_malloc(0, 0, 4, 0);
}

void	safe_exit(t_trash *trash, int exit_status)
{
	ft_lstclear(&trash, ft_del);
	rl_clear_history();
	exit(exit_status);
}

void	ft_del(void *content)
{
	free(content);
	content = NULL;
}
