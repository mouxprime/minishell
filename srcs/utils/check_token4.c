/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:55:37 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/15 12:12:36 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_operator_bis(t_token *token_node)
{
	if (token_node->type == 5 || token_node->type == 6 || token_node->type == 8
		|| !token_node->token)
		return (true);
	else
		return (false);
}

bool	check_token_redir(t_token *token)
{
	if (token->type == 1)
	{
		if (ft_strcmp(token->token, "<") != 0)
			return (error_token(token->token), false);
	}
	if (token->type == 2)
	{
		if (ft_strcmp(token->token, ">") != 0)
			return (error_token(token->token), false);
	}
	if (token->type == 3)
	{
		if (ft_strcmp(token->token, "<<") != 0)
			return (error_token(token->token), false);
	}
	if (token->type == 4)
	{
		if (ft_strcmp(token->token, ">>") != 0)
			return (error_token(token->token), false);
	}
	return (true);
}

bool	check_token_operator(t_token *token)
{
	if (token->type == 5)
	{
		if (ft_strcmp(token->token, "&&") != 0)
			return (error_token(token->token), false);
	}
	if (token->type == 6)
	{
		if (ft_strcmp(token->token, "||") != 0)
			return (error_token(token->token), false);
	}
	return (true);
}

bool	checking_token_bis(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	while (token)
	{
		if (is_operator_bis(token))
		{
			if (check_token_operator(token) == false)
				return (false);
			if (!token->next)
				return (error_token(token->token), false);
			if (is_operator_bis(token->prev) || is_operator_bis(token->next))
				return (error_token(token->token), false);
		}
		if (token->type >= 1 && token->type <= 4)
		{
			if (check_token_redir(token) == false)
				return (false);
		}
		token = token->next;
	}
	return (true);
}
