/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:55:49 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 17:38:01 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	define_token_type(t_token *token_list)
{
	if (token_list->token == NULL)
		token_list = token_list->next;
	while (token_list && token_list->token)
	{
		type_token(token_list);
		token_list = token_list->next;
	}
}

int	create_token_separator(t_token *token_list, char *command_line, int i)
{
	int		start;
	int		len;
	char	*str;

	len = 0;
	start = i;
	while (is_a_separator(command_line[i]))
	{
		i++;
		len++;
	}
	str = ft_substr(command_line, start, len, 0);
	new_token(token_list, str, 10);
	return (i);
}

t_token	*create_token(char *command_line)
{
	t_token	*token_list;
	int		i;

	i = 0;
	token_list = NULL;
	token_list = new_token(NULL, NULL, 0);
	while (command_line[i])
	{
		i = skip_spaces(command_line, i);
		if (command_line[i])
		{
			if (is_a_separator(command_line[i]) == true)
				i = create_token_separator(token_list, command_line, i);
			else
				token_loop_creation(token_list, command_line, &i);
		}
	}
	define_token_type(token_list);
	return (token_list);
}

t_token	*new_token(t_token *token_list, char *txt, int type)
{
	t_token	*new_node;
	t_token	*first_node;

	first_node = token_list;
	new_node = ft_malloc(1, sizeof(t_token), 0, 0);
	if (!new_node)
		return (NULL);
	if (!first_node)
	{
		new_node->token = NULL;
		new_node->prev = NULL;
		token_list = new_node;
		token_list->type = type;
	}
	else
	{
		while (first_node->next)
			first_node = first_node->next;
		first_node->next = new_node;
		new_node->prev = first_node;
		new_node->type = type;
		new_node->token = txt;
	}
	new_node->next = NULL;
	return (token_list);
}

bool	check_quotes(char *command_line, int single_quote, int parenthesis,
		int double_quote)
{
	int	i;

	i = 0;
	while (command_line[i])
	{
		if (command_line[i] == '"')
			double_quote++;
		if (command_line[i] == '(' && parenthesis % 2 == 0)
			parenthesis++;
		if (command_line[i] == ')' && parenthesis % 2 == 1)
			parenthesis++;
		if (command_line[i] == 39)
			single_quote++;
		i++;
	}
	if (double_quote % 2 == 0 && single_quote % 2 != 1 && parenthesis % 2 != 1)
		return (true);
	if (single_quote % 2 == 0 && double_quote % 2 != 1 && parenthesis % 2 != 1)
		return (true);
	if (parenthesis % 2 == 0 && single_quote % 2 != 1 && double_quote % 2 != 1)
		return (true);
	else
		return (false);
}
