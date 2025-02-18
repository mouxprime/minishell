/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:24:56 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 15:34:19 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_heredoc(char *token)
{
	ft_putstr_fd("Minishell: warning: here-document delimited by eof (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

void	error_token(char *token)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

int	perror_r(char *error_type, char *token)
{
	ft_putstr_fd(error_type, STDERR_FILENO);
	perror(token);
	return (-1);
}
