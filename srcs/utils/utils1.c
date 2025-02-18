/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:37:49 by mianni            #+#    #+#             */
/*   Updated: 2024/11/10 19:38:20 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*bool		check_parenthesis(char *command_line)
{
	int	i;

	i = 0;
	while (command_line[i])
	{
		if (command_line[i] == '(' && i != 0 && command_line[i - 1] != '$')
			return (false);
		i++;
	}
	return (true);
}*/
int	skip_spaces(char *command_line, int i)
{
	while ((command_line[i] == 32 || command_line[i] == '\t')
		&& command_line[i])
		i++;
	return (i);
}

bool	is_a_separator(char c)
{
	if (c == '&' || c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

bool	is_a_word(char *command_line, int i)
{
	if ((is_a_separator(command_line[i - 1]) == true)
		&& is_a_separator(command_line[i + 1]) == true)
		return (true);
	else
		return (false);
}

bool	is_a_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_a_special_space(char c)
{
	if (c == ' ' || c == '\t' || c == '$')
		return (true);
	return (false);
}
