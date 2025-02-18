/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mianni <mianni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:57:05 by mianni            #+#    #+#             */
/*   Updated: 2024/11/15 12:03:57 by mianni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token_list(t_token **token)
{
	t_token	*token_list;

	token_list = *token;
	while (token_list)
	{
		printf("\n---------------------\n");
		printf("Code = %d\n", token_list->type);
		printf("STR = %s$\n", token_list->token);
		printf("-----------------------\n");
		token_list = token_list->next;
	}
}

void	define_quoted_tokens(t_token *token_list)
{
	int	len;

	len = ft_strlen(token_list->token);
	if (token_list->token[0] == '\'' && !is_a_quote(token_list->token[len - 1]))
		token_list->type = 11;
	if (token_list->token[0] == '"' && !is_a_quote(token_list->token[len - 1]))
		token_list->type = 12;
}

static int	assign_type(t_token *token_list)
{
	if (token_list->token[0] == '<' && token_list->token[1] != '<')
		return (1);
	if (token_list->token[0] == '>' && token_list->token[1] != '>')
		return (2);
	if (token_list->token[0] == '<' && token_list->token[1] == '<')
		return (3);
	if (token_list->token[0] == '>' && token_list->token[1] == '>')
		return (4);
	if (token_list->token[0] == '&' && token_list->token[1] == '&')
		return (5);
	if (token_list->token[0] == '|' && token_list->token[1] == '|')
		return (6);
	if (token_list->token[0] == '(' && token_list->token[1] != ')')
		return (7);
	if (token_list->token[0] == '|' && token_list->token[1] == '\0')
		return (8);
	if (token_list->token[0] == '$' && variable_test(token_list->token))
		return (9);
	return (10);
}

void	type_token(t_token *token_list)
{
	if (token_list->token == NULL || token_list->type == 12
		|| token_list->type == 11 || token_list->type == 13)
		return ;
	token_list->type = assign_type(token_list);
}
